#include <iostream>
#include <pmonitor/pmonitor.h>
#include "saHCal.h"
#include <TH2.h>
#include <TF1.h>
#include <TFile.h>
#include <TStyle.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>

using namespace std;

int n_packet;
std::vector<int> index_packet;
std::vector<int> nchannel_packet;
std::vector<int> length_packet;

std::vector<float> signal_mean;
std::vector<float> signal_rms;

int n_hot_tower;
TH2F *h_pedestal_badchannel;
TH2F *h_temp;
std::vector<int> hot_packet_index;
std::vector<int> hot_channel_index;
std::vector<TH2F*> h_hot_signal;

int init_done = 0;
int do_hot_tower = 0;
int packet_health_check = 0;

std::ofstream general_info("../general_info.txt", std::ios::app);
std::ofstream run_info("../run_result/run_info.txt", std::ios::app);
TFile *run_hist = TFile::Open("../run_result/run_hist.root", "UPDATE");

void get_runtype(const char *filename) {
  std::string file_string(filename);
  size_t seb_position = file_string.find("seb");
  std::string number_string = file_string.substr(seb_position + 3, 2);
  int seb_index = std::atoi(number_string.c_str());

  if (seb_index >= 0 && seb_index <= 7) {
    n_packet = n_packet_emcal;
    index_packet.assign(index_packet_emcal, index_packet_emcal + n_packet_emcal);
    nchannel_packet.assign(nchannel_packet_emcal, nchannel_packet_emcal + n_packet_emcal);
    length_packet.assign(length_packet_emcal, length_packet_emcal + n_packet_emcal);
  } else if (seb_index == 14) {
    n_packet = n_packet_sepd + n_packet_zdc;
    index_packet.assign(index_packet_sepd, index_packet_sepd + n_packet_sepd);
    nchannel_packet.assign(nchannel_packet_sepd, nchannel_packet_sepd + n_packet_sepd);
    length_packet.assign(length_packet_sepd, length_packet_sepd + n_packet_sepd);
    index_packet.insert(index_packet.end(), index_packet_zdc, index_packet_zdc + n_packet_zdc);
    nchannel_packet.insert(nchannel_packet.end(), nchannel_packet_zdc, nchannel_packet_zdc + n_packet_zdc);
    length_packet.insert(length_packet.end(), length_packet_zdc, length_packet_zdc + n_packet_zdc);
  } else if (seb_index == 16 || seb_index == 17) {
    n_packet = n_packet_ihcal + n_packet_ohcal;
    index_packet.assign(index_packet_ihcal, index_packet_ihcal + n_packet_ihcal);
    nchannel_packet.assign(nchannel_packet_ihcal, nchannel_packet_ihcal + n_packet_ihcal);
    length_packet.assign(length_packet_ihcal, length_packet_ihcal + n_packet_ihcal);
    index_packet.insert(index_packet.end(), index_packet_ohcal, index_packet_ohcal + n_packet_ohcal);
    nchannel_packet.insert(nchannel_packet.end(), nchannel_packet_ohcal, nchannel_packet_ohcal + n_packet_ohcal);
    length_packet.insert(length_packet.end(), length_packet_ohcal, length_packet_ohcal + n_packet_ohcal);
  } else if (seb_index == 18) {
    n_packet = n_packet_mbd;
    index_packet.assign(index_packet_mbd, index_packet_mbd + n_packet_mbd);
    nchannel_packet.assign(nchannel_packet_mbd, nchannel_packet_mbd + n_packet_mbd);
    length_packet.assign(length_packet_mbd, length_packet_mbd + n_packet_mbd);
  } else {
    std::cout << "  Error: Bad file: " << file_string << std::endl;
    general_info << "  Error: Bad file: " << file_string << std::endl;
  }
}

int pinit() {
  gErrorIgnoreLevel = kError;
  h_pedestal_badchannel = new TH2F("h_pedestal_badchannel", "", n_packet, 0, n_packet, 192, 0, 192);
  h_pedestal_badchannel->GetXaxis()->SetTitle("Packet#");
  h_pedestal_badchannel->GetYaxis()->SetTitle("Channel#");
  gErrorIgnoreLevel = kPrint;
  return 0;
}

void find_hot_tower() {
  for (int ip = 0; ip < n_packet; ++ip) {
    for(int ic = 0; ic < nchannel_packet[ip]; ++ic) {
      if (h_pedestal_badchannel->GetBinContent(ip+1, ic+1) >= frequency_threshold) {
        hot_packet_index.push_back(index_packet[ip]);
        hot_channel_index.push_back(ic);
        h_temp = new TH2F(Form("h_hot_signal_%d_%d", index_packet[ip], ic), "", n_sample, 0, n_sample, 16384, 0 , 16384);
        h_temp->GetXaxis()->SetTitle("Sample#");
        h_temp->GetYaxis()->SetTitle("ADC");
        h_hot_signal.push_back(h_temp);
        run_info << index_packet[ip] << "  " << ic << "  " << h_pedestal_badchannel->GetBinContent(ip+1, ic+1) << std::endl;
        n_hot_tower++;
        do_hot_tower = 1;
      }
    }
  }
}

void output_hot_tower() {
  run_hist->cd();
  for (int ih = 0; ih < n_hot_tower; ++ih) {
    h_hot_signal[ih]->Write();
  }
  run_hist->Close();
}

int process_event (Event *e) {
  if (do_hot_tower == 0) {
    for(int ip = 0; ip < n_packet; ++ip) {
      for (int ic = 0; ic < nchannel_packet[ip]; ++ic) {
        signal_mean.push_back(0.);
        signal_rms.push_back(0.);
      }
      Packet *p = e->getPacket(index_packet[ip]);
      if(p && p->getLength() == length_packet[ip] && p->iValue(0,"CHANNELS") == nchannel_packet[ip]) {
        for(int ic = 0; ic < p->iValue(0, "CHANNELS") ; ++ic) {
          for(int is = 0; is < n_sample; ++is) {
            signal_mean[ic] += p->iValue(is, ic);
          }
        }
        for(int ic = 0; ic < p->iValue(0, "CHANNELS"); ++ic) {
          signal_mean[ic] /= (float)n_sample;
        }
        for(int ic = 0; ic < p->iValue(0, "CHANNELS"); ++ic) {
          for(int is = 0; is < n_sample; ++is) {
            signal_rms[ic] += (p->iValue(is, ic) - signal_mean[ic]) * (p->iValue(is, ic) - signal_mean[ic]);
          }
        }
        for(int ic = 0; ic < p->iValue(0, "CHANNELS"); ++ic) {
          signal_rms[ic] = TMath::Sqrt(signal_rms[ic] / (float)n_sample);
          if (signal_rms[ic] >= rms_threhold || signal_mean[ic] > mean_threshold) {
            h_pedestal_badchannel->Fill(ip, ic);
          }
        }
      }
      delete p;
      signal_mean.clear();
      signal_rms.clear();
    }
  } else {
    for (int ih = 0; ih < n_hot_tower; ++ih) {
      Packet *p = e->getPacket(hot_packet_index[ih]);
      for(int is = 0; is < n_sample; ++is) {
        h_hot_signal[ih]->Fill(is, p->iValue(is, hot_channel_index[ih]));
      }
      delete p;
    }
  }
  return 0;
}