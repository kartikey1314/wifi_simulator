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
class WiFi_5_Simulator{
private:
    vector<user> users;
    double totalDataTransmitted;
    double totalSimulationTime;
    vector<double> latencies;
public:
    WiFi_5_Simulator(int numUsers, int numPacketsPerUser)
        : totalDataTransmitted(0), totalSimulationTime(0){
        if(numUsers<=0 || numPacketsPerUser<=0){ 
            throw invalid_argument("Number of users and packets must be greater than zero.");
        }
        for(int i = 0; i < numUsers; ++i){
            user user(i);
            user.enqueuePacket(packet(CSI_SIZE));
            for (int j=0;j<numPacketsPerUser;j++) {
                user.enqueuePacket(packet(Pkt_size));
            }
            users.push_back(user);
        }
    }
    void simulate(double durationMs){
        double currentTime = 0;
        while (currentTime < durationMs){
            cout << "[INFO] Broadcast packet sent at " << currentTime << " ms.\n";
            currentTime += CSI_TRANSMISSION_TIME;
            for(auto& user : users){
                if (!user.hasCSI && user.hasPackets()){
                    packet csiPacket = user.dequeuePacket();
                    currentTime += CSI_TRANSMISSION_TIME;
                    user.hasCSI = true;
                    cout << "[INFO] user " << user.id << " sent CSI at " << currentTime << " ms.\n";
                }
            }
            cout << "[INFO] Parallel transmission starts at " << currentTime << " ms.\n";
            for(int i = 0; i < PARALLEL_TRANSMISSION_TIME / transmission_time; i++){
                for(auto& user : users){
                    if(user.hasCSI && user.hasPackets()){
                        packet dataPacket = user.dequeuePacket();
                        totalDataTransmitted += dataPacket.size;
                        double packetLatency = currentTime + transmission_time * i;
                        dataPacket.latency = packetLatency;
                        latencies.push_back(packetLatency);
                        cout << "[DEBUG] user " << user.id << " transmitted a packet at " << packetLatency << " ms.\n";
                    }
                }
            }
            currentTime += PARALLEL_TRANSMISSION_TIME;
            for(auto& user : users){
                user.hasCSI = false;
            }
        }
        totalSimulationTime = currentTime;
        cout << "[INFO] Simulation Complete. Total Time = " << totalSimulationTime << " ms\n";
    }
    double throughput() const{
        return (totalDataTransmitted * 8) / (totalSimulationTime * 1e3);
    }

    double averagelatency() const{
        double sum = accumulate(latencies.begin(), latencies.end(), 0.0);
        return latencies.empty() ? 0 : sum / latencies.size();
    }

    double maximumlatency() const{
        return latencies.empty() ? 0 : *max_element(latencies.begin(), latencies.end());
    }
};

// Main function
int main(){
    try{
        cout << "Test Case: 1 user, 100 Packets Each\n";
        WiFi_5_Simulator simulator1(1, 100);
        simulator1.simulate(1000);
        cout << "Throughput: " << simulator1.throughput() << " Mbps\n";
        cout << "Average Latency: " << simulator1.averagelatency() << " ms\n";
        cout << "Maximum Latency: " << simulator1.maximumlatency() << " ms\n";
        cout << "-----------\n";

        cout << "Test Case: 10 Users, 50 Packets Each\n";
        WiFi_5_Simulator simulator2(10, 50);
        simulator2.simulate(1000);
        cout << "Throughput: " << simulator2.throughput() << " Mbps\n";
        cout << "Average Latency: " << simulator2.averagelatency() << " ms\n";
        cout << "Maximum Latency: " << simulator2.maximumlatency() << " ms\n";
        cout << "-----------\n";

        cout << "Test Case: 100 Users, 20 Packets Each\n";
        WiFi_5_Simulator simulator3(100, 20);
        simulator3.simulate(1000);
        cout << "Throughput: " << simulator3.throughput() << " Mbps\n";
        cout << "Average Latency: " << simulator3.averagelatency() << " ms\n";
        cout << "Maximum Latency: " << simulator3.maximumlatency() << " ms\n";
        cout << "------------\n";

        cout << "Test Case: Zero Users\n";
        WiFi_5_Simulator simulatorInvalid1(0, 50); 
        simulatorInvalid1.simulate(1000);

        cout << "Test Case: Zero Packets\n";
        WiFi_5_Simulator simulatorInvalid2(10, 0);
        simulatorInvalid2.simulate(1000);

        cout << "Test Case: Negative Users\n";
        WiFi_5_Simulator simulatorInvalid3(-10, 50); 
        simulatorInvalid3.simulate(1000);

        cout << "Test Case: Negative Packets\n";
        WiFi_5_Simulator simulatorInvalid4(10, -50);
        simulatorInvalid4.simulate(1000);
    }
    catch (const invalid_argument& e){
        cout << "Error: " << e.what() << endl;
    }
    catch (const exception& e){
        cout << "An error occurred: " << e.what() << endl;
    }
}
