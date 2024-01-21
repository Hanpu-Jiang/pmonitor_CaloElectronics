#ifndef __SAHCAL_H__
#define __SAHCAL_H__

#include <pmonitor/pmonitor.h>
#include <Event/Event.h>
#include <Event/EventTypes.h>
#include <TFile.h>
#include <TH2F.h>
#include <fstream>
#include <iostream>
#include <vector>

int process_event (Event *e);
void get_runtype(const char *filename);
void find_hot_tower();
void output_hot_tower();

const float rms_threhold = 6;
const float mean_threshold = 7000;
const float frequency_threshold = 10;

const int n_packet_ihcal = 8;
const int index_packet_ihcal[n_packet_ihcal] = {7001, 7002, 7003, 7004, 7005, 7006, 7007, 7008};
const int nchannel_packet_ihcal[n_packet_ihcal] = {192, 192, 192, 192, 192, 192, 192, 192};
const int length_packet_ihcal[n_packet_ihcal] = {1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565};

const int n_packet_ohcal = 8;
const int index_packet_ohcal[n_packet_ohcal] = {8001, 8002, 8003, 8004, 8005, 8006, 8007, 8008};
const int nchannel_packet_ohcal[n_packet_ohcal] = {192, 192, 192, 192, 192, 192, 192, 192};
const int length_packet_ohcal[n_packet_ohcal] = {1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565};

const int n_packet_emcal = 128;
const int index_packet_emcal[n_packet_emcal] = {6001, 6002, 6003, 6004, 6005, 6006, 6007, 6008, 6009, 6010, 6011, 6012, 6013, 6014, 6015, 6016,
                                                6017, 6018, 6019, 6020, 6021, 6022, 6023, 6024, 6025, 6026, 6027, 6028, 6029, 6030, 6031, 6032,
                                                6033, 6034, 6035, 6036, 6037, 6038, 6039, 6040, 6041, 6042, 6043, 6044, 6045, 6046, 6047, 6048,
                                                6049, 6050, 6051, 6052, 6053, 6054, 6055, 6056, 6057, 6058, 6059, 6060, 6061, 6062, 6063, 6064,
                                                6065, 6066, 6067, 6068, 6069, 6070, 6071, 6072, 6073, 6074, 6075, 6076, 6077, 6078, 6079, 6080,
                                                6081, 6082, 6083, 6084, 6085, 6086, 6087, 6088, 6089, 6090, 6091, 6092, 6093, 6094, 6095, 6096,
                                                6097, 6098, 6099, 6100, 6101, 6102, 6103, 6104, 6105, 6106, 6107, 6108, 6109, 6110, 6111, 6112,
                                                6113, 6114, 6115, 6116, 6117, 6118, 6119, 6120, 6121, 6122, 6123, 6124, 6125, 6126, 6127, 6128};
const int nchannel_packet_emcal[n_packet_emcal] = {192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192,
                                                   192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192,
                                                   192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192,
                                                   192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192,
                                                   192, 128, 192, 192, 192, 128, 192, 192, 192, 128, 192, 192, 192, 128, 192, 192,
                                                   192, 128, 192, 192, 192, 128, 192, 192, 192, 128, 192, 192, 192, 128, 192, 192,
                                                   192, 128, 192, 192, 192, 128, 192, 192, 192, 128, 192, 192, 192, 128, 192, 192,
                                                   192, 128, 192, 192, 192, 128, 192, 192, 192, 128, 192, 192, 192, 128, 192, 192};
const int length_packet_emcal[n_packet_emcal] = {1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565,
                                                1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565,
                                                1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565,
                                                1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565, 1565,
                                                1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565,
                                                1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565,
                                                1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565,
                                                1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565, 1565, 1047, 1565, 1565};

const int n_packet_mbd = 2;
const int index_packet_mbd[n_packet_mbd] = {1001, 1002};
const int nchannel_packet_mbd[n_packet_mbd] = {128, 128};
const int length_packet_mbd[n_packet_mbd] = {3991, 3991};

const int n_packet_sepd = 6;
const int index_packet_sepd[n_packet_sepd] = {9001, 9002, 9003, 9004, 9005, 9006};
const int nchannel_packet_sepd[n_packet_sepd] = {128, 128, 128, 128, 128, 128};
const int length_packet_sepd[n_packet_sepd] = {1047, 1047, 1047, 1047, 1047, 1047};

const int n_packet_zdc = 1;
const int index_packet_zdc[n_packet_zdc] = {12001};
const int nchannel_packet_zdc[n_packet_zdc] = {64};
const int length_packet_zdc[n_packet_zdc] = {529};

const int n_sample = 12;

#endif /* __SAHCAL_H__ */