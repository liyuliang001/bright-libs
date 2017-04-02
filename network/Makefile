CFLAGS = -std=gnu++11 -O2
SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = target
INSTALL_LIB_DIR=/usr/local/lib
INSTALL_INCLUDE_DIR=/usr/local/include/bright_lib/network
all: $(BUILD_DIR)/packet.o $(BUILD_DIR)/pcap_record.o $(BUILD_DIR)/pcap_parser.o

$(TARGET_DIR):
	mkdir $(TARGET_DIR)
$(BUILD_DIR):
	mkdir $(BUILD_DIR) 
$(BUILD_DIR)/packet.o : $(BUILD_DIR) $(SRC_DIR)/packet.hpp $(SRC_DIR)/packet.cpp
	g++ $(SRC_DIR)/packet.cpp $(CFLAGS) -c -o $(BUILD_DIR)/packet.o
$(BUILD_DIR)/pcap_record.o : $(BUILD_DIR) $(SRC_DIR)/pcap_record.hpp $(SRC_DIR)/pcap_record.cpp $(SRC_DIR)/packet.hpp
	g++ $(SRC_DIR)/pcap_record.cpp $(CFLAGS) -c -o $(BUILD_DIR)/pcap_record.o
$(BUILD_DIR)/pcap_parser.o : $(BUILD_DIR) $(SRC_DIR)/pcap_parser.hpp $(SRC_DIR)/pcap_parser.cpp $(SRC_DIR)/packet.hpp $(SRC_DIR)/pcap_record.hpp
	g++ $(SRC_DIR)/pcap_parser.cpp $(CFLAGS) -c -o $(BUILD_DIR)/pcap_parser.o

$(TARGET_DIR)/libnetwork.a : $(TARGET_DIR) $(BUILD_DIR)/packet.o $(BUILD_DIR)/pcap_record.o $(BUILD_DIR)/pcap_parser.o
	ar crv $(TARGET_DIR)/libnetwork.a $(BUILD_DIR)/packet.o $(BUILD_DIR)/pcap_record.o $(BUILD_DIR)/pcap_parser.o

install: $(TARGET_DIR)/libnetwork.a
	if [ ! -d "$(INSTALL_INCLUDE_DIR)" ]; then mkdir $(INSTALL_INCLUDE_DIR); fi
	cp $(SRC_DIR)/packet.hpp $(INSTALL_INCLUDE_DIR)/packet.hpp
	cp $(SRC_DIR)/pcap_record.hpp $(INSTALL_INCLUDE_DIR)/pcap_record.hpp
	cp $(SRC_DIR)/pcap_parser.hpp $(INSTALL_INCLUDE_DIR)/pcap_parser.hpp
	cp $(TARGET_DIR)/libnetwork.a $(INSTALL_LIB_DIR)/libnetwork.a

clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(TARGET_DIR)/*
	rm -rf $(INSTALL_INCLUDE_DIR)
