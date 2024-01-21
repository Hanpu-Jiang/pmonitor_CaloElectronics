void count_hot_tower() {
  const int n_channel_emcal = 24576;
  int channel_count_emcal[n_channel_emcal] = {0};
  std::vector<std::vector<int>> channel_runnumber_emcal(n_channel_emcal);
  const int n_channel_ihcal = 1536;
  int channel_count_ihcal[n_channel_ihcal] = {0};
  std::vector<std::vector<int>> channel_runnumber_ihcal(n_channel_ihcal);
  const int n_channel_ohcal = 1536;
  int channel_count_ohcal[n_channel_ohcal] = {0};
  std::vector<std::vector<int>> channel_runnumber_ohcal(n_channel_ohcal);
  const int n_channel_mbd = 256;
  int channel_count_mbd[n_channel_mbd] = {0};
  std::vector<std::vector<int>> channel_runnumber_mbd(n_channel_mbd);
  const int n_channel_sepd = 768;
  int channel_count_sepd[n_channel_sepd] = {0};
  std::vector<std::vector<int>> channel_runnumber_sepd(n_channel_sepd);
  const int n_channel_zdc = 64;
  int channel_count_zdc[n_channel_zdc] = {0};
  std::vector<std::vector<int>> channel_runnumber_zdc(n_channel_zdc);

  std::ifstream file_input("hot_tower_list.txt");
  std::ofstream file_output("../hot_tower_summary.txt");

  int run_number, packet_number, channel_number, n_entry, channel_index;

  while (file_input >> run_number >> packet_number >> channel_number >> n_entry) {
    if (packet_number >= 6001 && packet_number <= 6128) {
      channel_index = (packet_number - 6001) * 192 + channel_number;
      channel_runnumber_emcal[channel_index].push_back(run_number);
      channel_count_emcal[channel_index]++;
    } else if (packet_number >= 7001 && packet_number <= 7008) {
      channel_index = (packet_number - 7001) * 192 + channel_number;
      channel_runnumber_ihcal[channel_index].push_back(run_number);
      channel_count_ihcal[channel_index]++;
    } else if (packet_number >= 8001 && packet_number <= 8008) {
      channel_index = (packet_number - 8001) * 192 + channel_number;
      channel_runnumber_ohcal[channel_index].push_back(run_number);
      channel_count_ohcal[channel_index]++;
    } else if (packet_number >= 1001 && packet_number <= 1002) {
      channel_index = (packet_number - 1001) * 128 + channel_number;
      channel_runnumber_mbd[channel_index].push_back(run_number);
      channel_count_mbd[channel_index]++;
    } else if (packet_number >= 9001 && packet_number <= 9006) {
      channel_index = (packet_number - 9001) * 128 + channel_number;
      channel_runnumber_sepd[channel_index].push_back(run_number);
      channel_count_sepd[channel_index]++;
    } else if (packet_number == 12001) {
      channel_index = channel_number;
      channel_runnumber_zdc[channel_index].push_back(run_number);
      channel_count_zdc[channel_index]++;
    }
  }

  file_output << "Channel_index\tPacket_index\tTower_index\t#hot_run\tRun_number" << std::endl;
  file_output << std::endl << std::endl << "EMCal" << std::endl;
  for (int i = 0; i < n_channel_emcal; i++) {
    if (channel_count_emcal[i] >= 1) {
      file_output << i << "\t" << i/192+6001 << "\t" << i%192 << "\t" << channel_count_emcal[i] << "\t";
      file_output << channel_runnumber_emcal[i][0];
      for (int j = 1; j < channel_count_emcal[i]; j++) {
        file_output << ", " << channel_runnumber_emcal[i][j];
      }
      file_output << std::endl;
    }
  }
  file_output << std::endl << std::endl << "IHCal" << std::endl;
  for (int i = 0; i < n_channel_ihcal; i++) {
    if (channel_count_ihcal[i] >= 1) {
      file_output << i << "\t" << i/192+7001 << "\t" << i%192 << "\t" << channel_count_ihcal[i] << "\t";
      file_output << channel_runnumber_ihcal[i][0];
      for (int j = 1; j < channel_count_ihcal[i]; j++) {
        file_output << ", " << channel_runnumber_ihcal[i][j];
      }
      file_output << std::endl;
    }
  }
  file_output << std::endl << std::endl << "OHCal" << std::endl;
  for (int i = 0; i < n_channel_ohcal; i++) {
    if (channel_count_ohcal[i] >= 1) {
      file_output << i << "\t" << i/192+8001 << "\t" << i%192 << "\t" << channel_count_ohcal[i] << "\t";
      file_output << channel_runnumber_ohcal[i][0];
      for (int j = 1; j < channel_count_ohcal[i]; j++) {
        file_output << ", " << channel_runnumber_ohcal[i][j];
      }
      file_output << std::endl;
    }
  }
  file_output << std::endl << std::endl << "MBD" << std::endl;
  for (int i = 0; i < n_channel_mbd; i++) {
    if (channel_count_mbd[i] >= 1) {
      file_output << i << "\t" << i/128+1001 << "\t" << i%128 << "\t" << channel_count_mbd[i] << "\t";
      file_output << channel_runnumber_mbd[i][0];
      for (int j = 1; j < channel_count_mbd[i]; j++) {
        file_output << ", " << channel_runnumber_mbd[i][j];
      }
      file_output << std::endl;
    }
  }
  file_output << std::endl << std::endl << "SEPD" << std::endl;
  for (int i = 0; i < n_channel_sepd; i++) {
    if (channel_count_sepd[i] >= 1) {
      file_output << i << "\t" << i/128+9001 << "\t" << i%128 << "\t" << channel_count_sepd[i] << "\t";
      file_output << channel_runnumber_sepd[i][0];
      for (int j = 1; j < channel_count_sepd[i]; j++) {
        file_output << ", " << channel_runnumber_sepd[i][j];
      }
      file_output << std::endl;
    }
  }
  file_output << std::endl << std::endl << "ZDC" << std::endl;
  for (int i = 0; i < n_channel_zdc; i++) {
    if (channel_count_zdc[i] >= 1) {
      file_output << i << "\t" << 12001 << "\t" << i << "\t" << channel_count_zdc[i] << "\t";
      file_output << channel_runnumber_zdc[i][0];
      for (int j = 1; j < channel_count_zdc[i]; j++) {
        file_output << ", " << channel_runnumber_zdc[i][j];
      }
      file_output << std::endl;
    }
  }
}