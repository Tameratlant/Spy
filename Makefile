C = g++
CXXFLAGS = -Wall -g
BUILD_DIR = build

all: $(BUILD_DIR)/separete $(BUILD_DIR)/main

$(BUILD_DIR)/separete: separete.cpp
 mkdir -p $(BUILD_DIR)
 $(C) $(CFLAGS) -o $@ $<

$(BUILD_DIR)/main: main.cpp $(BUILD_DIR)/separete
 $(C) $(CFLAGS) -o $@ $<

run_separete: $(BUILD_DIR)/separete
 ./$(BUILD_DIR)/separete

clean:
 rm -rf $(BUILD_DIR)
