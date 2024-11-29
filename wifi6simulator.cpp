#include<bits/stdc++.h>

using namespace std;

// Constants
const int pkt_size = 1024;
const int CSI_SIZE = 200;
const double bandwidth = 20e6;
const double modulation = log2(256);
const double coding_rate = 5.0 / 6.0;
const double data_rate = bandwidth * modulation * coding_rate;
const double PARALLEL_TRANSMISSION_TIME = 5.0;
const int SUBCHANNELS[] = {10, 4, 2};

class Packet{
public:
    int size;
    double latency;
    Packet(int size) : size(size), latency(0){}
};

class User{
public:
    int id;
    queue<Packet> packetQueue;
    bool hasCSI;
    User(int id) : id(id), hasCSI(false){}
    void enqueuePacket(Packet p){
        packetQueue.push(p);
    }
    bool hasPackets() const{
        return !packetQueue.empty();
    }
    Packet dequeuePacket(){
        Packet p = packetQueue.front();
        packetQueue.pop();
        return p;
    }
};

class WiFi6Simulator{
private:
    vector<User> users;
    double totalDataTransmitted;
    double totalSimulationTime;
    vector<double> latencies;

public:
    WiFi6Simulator(int numUsers, int numPacketsPerUser)
        : totalDataTransmitted(0), totalSimulationTime(0){
        if (numUsers <= 0 || numPacketsPerUser <= 0) {
            throw invalid_argument("Number of users and packets must be greater than zero.");
        }
        for (int i = 0; i < numUsers; i++){
            User user(i);
            user.enqueuePacket(Packet(CSI_SIZE));
            for (int j = 0; j < numPacketsPerUser; j++){
                user.enqueuePacket(Packet(pkt_size));
            }
            users.push_back(user);
        }
    }

    void simulate(double durationMs){
        double currentTime = 0;
        int subChannelIndex = 0;

        while (currentTime < durationMs){
            cout << "[INFO] Broadcast packet sent at " << currentTime << " ms.\n";
            currentTime += PARALLEL_TRANSMISSION_TIME;
            for (auto& user : users) {
                if (!user.hasCSI && user.hasPackets()){
                    Packet csiPacket = user.dequeuePacket();
                    currentTime += (CSI_SIZE * 8) / (data_rate / SUBCHANNELS[subChannelIndex]);
                    user.hasCSI = true;
                    cout << "[INFO] User " << user.id << " sent CSI at " << currentTime << " ms.\n";
                }
            }
            cout << "[INFO] Parallel transmission starts at " << currentTime << " ms.\n";
            for (int subChannel : SUBCHANNELS){
                for (auto& user : users){
                    if (user.hasCSI && user.hasPackets()){
                        Packet dataPacket = user.dequeuePacket();
                        totalDataTransmitted += dataPacket.size;
                        double transmissionTime = (dataPacket.size * 8) / (data_rate / subChannel) * 1000;
                        currentTime += transmissionTime;
                        dataPacket.latency = currentTime;
                        latencies.push_back(dataPacket.latency);
                        cout << "[DEBUG] User " << user.id << " transmitted a packet on " << subChannel
                             << " MHz subchannel at " << currentTime << " ms.\n";
                    }
                }
            }

            currentTime += PARALLEL_TRANSMISSION_TIME;
            for (auto& user : users){
                user.hasCSI = false;
            }
        }

        totalSimulationTime = currentTime;
        cout << "[INFO] Simulation Complete. Total Time = " << totalSimulationTime << " ms\n";
    }

    double calculateThroughput() const{
        return (totalDataTransmitted * 8) / (totalSimulationTime * 1e3);
    }

    double calculateAverageLatency() const{
        double sum = accumulate(latencies.begin(), latencies.end(), 0.0);
        return latencies.empty() ? 0 : sum / latencies.size();
    }

    double calculateMaximumLatency() const{
        return latencies.empty() ? 0 : *max_element(latencies.begin(), latencies.end());
    }
};

int main(){
    try {
        cout << "Test Case: 1 User, 100 Packets Each\n";
        WiFi6Simulator simulator1(1, 100);
        simulator1.simulate(1000);
        cout << "Throughput: " << simulator1.calculateThroughput() << " Mbps\n";
        cout << "Average Latency: " << simulator1.calculateAverageLatency() << " ms\n";
        cout << "Maximum Latency: " << simulator1.calculateMaximumLatency() << " ms\n";
        cout << "--------------------------------------\n";
        cout << "Test Case: 10 Users, 50 Packets Each\n";
        WiFi6Simulator simulator2(10, 50);
        simulator2.simulate(1000);
        cout << "Throughput: " << simulator2.calculateThroughput() << " Mbps\n";
        cout << "Average Latency: " << simulator2.calculateAverageLatency() << " ms\n";
        cout << "Maximum Latency: " << simulator2.calculateMaximumLatency() << " ms\n";
        cout << "--------------------------------------\n";
        cout << "Test Case: 100 Users, 20 Packets Each\n";
        WiFi6Simulator simulator3(100, 20);
        simulator3.simulate(1000); 
        cout << "Throughput: " << simulator3.calculateThroughput() << " Mbps\n";
        cout << "Average Latency: " << simulator3.calculateAverageLatency() << " ms\n";
        cout << "Maximum Latency: " << simulator3.calculateMaximumLatency() << " ms\n";
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}
