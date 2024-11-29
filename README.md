<<<<<<< HEAD
# Wi-Fi-Simulator
The goal of this project is to use C++'s Object-Oriented Programming ideas to create a basic WiFi simulator that can model and simulate several WiFi communication methods, including WiFi 4, WiFi 5, and WiFi 6.

Wi-Fi Communication Simulation
Project Overview
This project simulates Wi-Fi communication using various Wi-Fi standards: WiFi 4 (802.11n), WiFi 5 (802.11ac), and WiFi 6 (802.11ax). It models communication scenarios such as channel contention, parallel transmissions, and sub-channel allocation to evaluate throughput, latency, and performance.

Key Features
WiFi 4 Simulation: Simulates a shared channel where users attempt to transmit data packets, using backoff strategies to handle contention.

WiFi 5 Simulation: Implements Multi-User MIMO (MU-MIMO) where users first send Channel State Information (CSI) and then transmit data packets in parallel for a fixed duration.

WiFi 6 Simulation: Simulates Orthogonal Frequency-Division Multiple Access (OFDMA), where the 20 MHz channel is divided into smaller sub-channels of size 2 MHz, 4 MHz, or 10 MHz, and users transmit in parallel using round-robin scheduling.
The main performance metrics that are calculated include:

Throughput: Total data successfully transmitted during the simulation.
Average Latency: The average time taken for packets to reach their destination.
Maximum Latency: The longest time taken for any packet.
Simulation Scenarios
WiFi 4 Simulation (802.11n)
Scenario: Simulates a situation where multiple users attempt to access a shared communication channel and transmit data packets. Contention between users is managed by introducing backoff times.
WiFi 5 Simulation (802.11ac)
Scenario: Multi-User MIMO (MU-MIMO) where users first send Channel State Information (CSI) and then transmit data in parallel over a 15 ms period. This process is repeated periodically.
WiFi 6 Simulation (802.11ax)
Scenario: Implements OFDMA, where the 20 MHz channel is divided into smaller sub-channels (2 MHz, 4 MHz, 10 MHz). Users are allocated sub-channels in a round-robin manner, and each user transmits over a sub-channel for 5 ms.
Technologies and Concepts Used
C++ programming language for simulation development.
OFDMA and MU-MIMO are used to simulate efficient multi-user communication.
Backoff Mechanism to handle contention in WiFi 4 simulation.
Installation & Running the Program
Prerequisites
C++ Compiler: Make sure you have a C++ compiler such as g++ installed on your machine.
VS Code: Recommended IDE for development.
Steps to Install
Clone or download the repository.
Navigate to the project directory where the C++ files are stored.
Open the terminal in the project directory.
Steps to Run
Build the Program Using Makefile:

Ensure you have a Makefile in the project directory.
In the terminal, run the following command:
mingw32-make

Run the Executable:
After building the program, run the executable for each simulation scenario by typing the following command:
bash
./wifi_simulator
Test Cases:
The program will run various test cases for WiFi 4, WiFi 5, and WiFi 6 simulations. The results will show throughput, average latency, and maximum latency for each test case.
Code Structure
wifi4simulator.cpp: Contains the simulation code for WiFi 4.
wifi5simulator.cpp: Contains the simulation code for WiFi 5.
wifi6simulator.cpp: Contains the simulation code for WiFi 6.
Makefile: A makefile for compiling and running the simulations.
Running Test Cases
In the main function, the following test cases are implemented:

WiFi 4: Simulate 1 user with 100 packets, 10 users with 50 packets, and 100 users with 20 packets.
WiFi 5: Simulate 1 user with 100 packets, 10 users with 50 packets, and 100 users with 20 packets.
WiFi 6: Similar test cases as in WiFi 4 and WiFi 5.
Invalid Test Cases:
Test cases for zero users or zero packets will raise an error and provide appropriate feedback.

Project Contributions
Developed by: Kartikey Singh
Under the guidance of: Arani Bhattacharya Sir
Credit to: IIITD (Indraprastha Institute of Information Technology Delhi)
Sources: Various resources from the internet and AI tools were used for coding and algorithm implementations.
Licenses

This project is for educational purposes and follows the open-source model. Feel free to modify or enhance the code as per your needs.

Acknowledgments
I would like to express my sincere gratitude to Arani Bhattacharya Sir for his guidance throughout the project, and to the IIITD for providing the resources and environment to complete this work.
