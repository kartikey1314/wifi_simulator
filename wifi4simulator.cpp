#include<bits/stdc++.h>

using namespace std;

const int PACKET_SIZE = 1024; // Packet size in bytes = 1 KB
const double BANDWIDTH = 20e6; // Bandwidth in Hz =20 MHz
const double MODULATION = log2(256); // 256-QAM -> log2(256) = 8 bits/symbol
const double CODING_RATE = 5.0 / 6.0; // Coding rate
const double DATA_RATE = BANDWIDTH * MODULATION * CODING_RATE; // Effective data rate in bits/s
const double TRANSMISSION_TIME = (PACKET_SIZE * 8) / DATA_RATE * 1000; // Time to transmit 1 packet in ms
const double MAX_BACKOFF_TIME = 10.0; // Max backoff time in ms

// Random number generator for backoff time
double getRandomBackoffTime() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0, MAX_BACKOFF_TIME);
    return dis(gen);
}
// Packet 
class Packet {
public:
    int size;
    double latency;
    Packet(int size) {
        this->size = size;
        this->latency = 0;
    }
};

// User class
class User {
public:
    int id;
    queue<Packet> packet_Queue;
    double backoffTimeRemaining; // Time the user must wait before retrying

    User(int id) {
        this->id = id;
        this->backoffTimeRemaining = 0;
    }
    bool hasPackets() const{
        return packet_Queue.size()!=0;
    }
    void enqueuePacket(Packet p){
        packet_Queue.push(p);
    }
    Packet dequeuePacket(){
        Packet p = packet_Queue.front();
        packet_Queue.pop();
        return p;
    }
};