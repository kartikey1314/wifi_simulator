#include<bits/stdc++.h>

using namespace std;

const int Pkt_size = 1024; 
const double bandwidth = 20e6; 
const double modulation = log2(256); 
const double coding_rate = 5.0/6.0;
const double data_rate = bandwidth*modulation*coding_rate;
const double transmission_time = (Pkt_size*8)/data_rate*1000;
const double max_backoff_time = 10.0;

double getRandomBackoffTime(){
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_real_distribution<> dis(0, max_backoff_time);
    return dis(gen);
}
class Packet{
public:
    int size;
    double latency;
    Packet(int size) {
        this->size = size;
        this->latency = 0;
    }
};
class User{
public:
    int id;
    queue<Packet> packet_Queue;
    double backoff_time_rem;

    User(int id) {
        this->id = id;
        this->backoff_time_rem = 0;
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
class WiFi4Simulator{
private:
    bool channelFree;
    vector<User> users;
    double totalDataTransmitted;
    double totalSimulationTime;
    vector<double> latencies;
    long int channelBusyCount; 

public:
    WiFi4Simulator(int numuser, int numpktperuser)
        : channelFree(true),totalDataTransmitted(0),totalSimulationTime(0),channelBusyCount(0){
        if (numuser<=0||numpktperuser<=0){
            cout << "error: Invalid number of users or packets.\n";
            return;
        }
        for (int i = 0;i<numuser; i++) {
            User user(i);
            for (int j = 0;j<numpktperuser;j++) {
                user.enqueuePacket(Packet(Pkt_size));
            }
            users.push_back(user);
        }
    }

    void simulate(double durationMs) {
        if (users.empty()){
            cout << "error: No valid users to simulate.\n";
            return;
        }
        double currentTime = 0;  
        double channelBusyUntil = 0;

        while (currentTime < durationMs){
            bool progress = false;
            vector<int> users_Attempting; 

            for (size_t i = 0;i<users.size();i++){
                if (!users[i].hasPackets()) {
                    continue;
                }
                if (users[i].backoff_time_rem>0) {
                    users[i].backoff_time_rem = users[i].backoff_time_rem-transmission_time;
                    progress = true;
                    continue;
                }
                users_Attempting.push_back(i);
            }

            if (users_Attempting.size()>1){
                for (size_t i = 1;i<users_Attempting.size();i++) {
                    channelBusyCount++;
                    users[users_Attempting[i]].backoff_time_rem = getRandomBackoffTime();
                }
            }

            if (!users_Attempting.empty() && currentTime>=channelBusyUntil) {
                int transmittingUser = users_Attempting[0];
                Packet packet = users[transmittingUser].dequeuePacket();
                channelBusyUntil = currentTime + transmission_time;
                packet.latency = channelBusyUntil;
                latencies.push_back(packet.latency);
                totalDataTransmitted += packet.size;
                progress = true;
            }
            if (!progress) {
                break;
            }
            currentTime = max(currentTime, channelBusyUntil);
        }
        totalSimulationTime = currentTime;
    }
    double calculateThroughput() const{
        return (totalDataTransmitted * 8) / (totalSimulationTime * 1e3);
    }
    double calculateAverageLatency() const{
        double sum = accumulate(latencies.begin(), latencies.end(), 0.0);
        if (latencies.empty()) {
            return 0.0;
        } else {
            return sum / latencies.size();
        }
    }

    double calculateMaximumLatency() const{
        if (latencies.empty()) {
            return 0.0;
        } else {
            double maxLatency = *std::max_element(latencies.begin(), latencies.end());
        return maxLatency;
    }
    }

    int getChannelBusyCount() const{
        return channelBusyCount;
    }
};


