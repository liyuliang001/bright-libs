CFLAGS = -std=gnu++11 -O3
SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = target
INSTALL_LIB_DIR=/usr/local/lib
INSTALL_INCLUDE_DIR=/usr/local/include/bright_lib/tcp_socket
all: $(BUILD_DIR)/client.o $(BUILD_DIR)/server.o $(BUILD_DIR)/tcp_socket.o

$(TARGET_DIR):
	mkdir $(TARGET_DIR)
$(BUILD_DIR):
	mkdir $(BUILD_DIR) 
$(BUILD_DIR)/client.o : $(BUILD_DIR) $(SRC_DIR)/client.hpp $(SRC_DIR)/client.cpp
	g++ $(SRC_DIR)/client.cpp $(CFLAGS) -c -o $(BUILD_DIR)/client.o
$(BUILD_DIR)/server.o : $(BUILD_DIR) $(SRC_DIR)/server.hpp $(SRC_DIR)/server.cpp
	g++ $(SRC_DIR)/server.cpp $(CFLAGS) -c -o $(BUILD_DIR)/server.o
$(BUILD_DIR)/tcp_socket.o : $(BUILD_DIR) $(SRC_DIR)/tcp_socket.hpp $(SRC_DIR)/tcp_socket.cpp
	g++ $(SRC_DIR)/tcp_socket.cpp $(CFLAGS) -c -o $(BUILD_DIR)/tcp_socket.o

$(TARGET_DIR)/libtcp_socket.a : $(TARGET_DIR) $(BUILD_DIR)/client.o $(BUILD_DIR)/server.o $(BUILD_DIR)/tcp_socket.o
	ar crv $(TARGET_DIR)/libtcp_socket.a $(BUILD_DIR)/client.o $(BUILD_DIR)/server.o $(BUILD_DIR)/tcp_socket.o

install: $(TARGET_DIR)/libtcp_socket.a
	if [ ! -d "$(INSTALL_INCLUDE_DIR)" ]; then mkdir $(INSTALL_INCLUDE_DIR); fi
	cp $(SRC_DIR)/client.hpp $(INSTALL_INCLUDE_DIR)/client.hpp
	cp $(SRC_DIR)/server.hpp $(INSTALL_INCLUDE_DIR)/server.hpp
	cp $(SRC_DIR)/tcp_socket.hpp $(INSTALL_INCLUDE_DIR)/tcp_socket.hpp
	cp $(TARGET_DIR)/libtcp_socket.a $(INSTALL_LIB_DIR)/libtcp_socket.a

clean:
	rm -f $(BUILD_DIR)/*
	rm -f $(TARGET_DIR)/*
	rm -rf $(INSTALL_INCLUDE_DIR)
	rm $(INSTALL_LIB_DIR)/libtcp_socket.a
