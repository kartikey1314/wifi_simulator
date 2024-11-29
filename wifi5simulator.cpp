#include<bits/stdc++.h>

using namespace std;

const int Pkt_size = 1024; 
const int CSI_SIZE = 200;    
const double bandwidth = 20e6; 
const double modulation= log2(256);
const double coding_rate = 5.0 / 6.0;
const double data_rate = bandwidth * modulation* coding_rate; 
const double transmission_time = (Pkt_size * 8) / data_rate * 1000; 
const double CSI_TRANSMISSION_TIME = (CSI_SIZE * 8) / data_rate * 1000; 
const double PARALLEL_TRANSMISSION_TIME = 15.0; 

class packet{
public:
    int size;
    double latency;
    packet(int size) : size(size), latency(0) {}
};
class user{
public:
    int id;
    queue<packet> packetQueue;
    bool hasCSI;
    user(int id) : id(id), hasCSI(false) {}
    void enqueuePacket(packet p) {
        packetQueue.push(p);
    }
    bool hasPackets() const {
        return !packetQueue.empty();
    }
    packet dequeuePacket() {
        packet p = packetQueue.front();
        packetQueue.pop();
        return p;
    }
};

