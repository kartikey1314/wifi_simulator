# Compiler
CXX := g++

# Compiler Flags
CXXFLAGS := -Wall -Wextra -std=c++17

# Source Files
SRC_FILES := wifi4simulator.cpp wifi5simulator.cpp wifi6simulator.cpp

# Object Files
OBJ_FILES := $(SRC_FILES:.cpp=.o)

# Output Executables
TARGETS := wifi4simulator wifi5simulator wifi6simulator

# Default Target
all: $(TARGETS)

# Build Targets
wifi4simulator: wifi4simulator.o
	$(CXX) $(CXXFLAGS) -o wifi4simulator wifi4simulator.o

wifi5simulator: wifi5simulator.o
	$(CXX) $(CXXFLAGS) -o wifi5simulator wifi5simulator.o

wifi6simulator: wifi6simulator.o
	$(CXX) $(CXXFLAGS) -o wifi6simulator wifi6simulator.o

# Compilation Rule for .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Test Target
test: all
	@echo "Running WiFi 4 Simulator Tests..."
	./wifi4simulator
	@echo "Running WiFi 5 Simulator Tests..."
	./wifi5simulator
	@echo "Running WiFi 6 Simulator Tests..."
	./wifi6simulator

# Clean Target
clean:
	rm -f $(TARGETS) $(OBJ_FILES)

# Run Specific Simulation
run_wifi4:
	./wifi4simulator

run_wifi5:
	./wifi5simulator

run_wifi6:
	./wifi6simulator

# Help Target
help:
	@echo "Makefile for WiFi Simulators"
	@echo "Available Targets:"
	@echo "  all          - Build all simulators"
	@echo "  wifi4simulator - Build WiFi 4 simulator"
	@echo "  wifi5simulator - Build WiFi 5 simulator"
	@echo "  wifi6simulator - Build WiFi 6 simulator"
	@echo "  test         - Build and run all simulators"
	@echo "  clean        - Remove build artifacts"
	@echo "  run_wifi4    - Run WiFi 4 simulator"
	@echo "  run_wifi5    - Run WiFi 5 simulator"
	@echo "  run_wifi6    - Run WiFi 6 simulator"
