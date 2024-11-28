#include<bits/stdc++.h>

using namespace std;

const int PACKET_SIZE = 1024; // Packet size in bytes = 1 KB
const double BANDWIDTH = 20e6; // Bandwidth in Hz =20 MHz
const double MODULATION = log2(256); // 256-QAM -> log2(256) = 8 bits/symbol
const double CODING_RATE = 5.0 / 6.0; // Coding rate
const double DATA_RATE = BANDWIDTH * MODULATION * CODING_RATE; // Effective data rate in bits/s
const double TRANSMISSION_TIME = (PACKET_SIZE * 8) / DATA_RATE * 1000; // Time to transmit 1 packet in ms
const double MAX_BACKOFF_TIME = 10.0; // Max backoff time in ms


