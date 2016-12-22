SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = target
INSTALL_LIB_DIR=/usr/local/lib
INSTALL_INCLUDE_DIR=/usr/local/include/bright_lib/serde
all: $(TARGET_DIR)/serde.o

$(TARGET_DIR):
	mkdir $(TARGET_DIR)
$(BUILD_DIR):
	mkdir $(BUILD_DIR) 
$(BUILD_DIR)/serde.o : $(BUILD_DIR) $(SRC_DIR)/serde.cpp $(SRC_DIR)/serde.hpp
	g++ $(SRC_DIR)/serde.cpp -O2 -c -o $(BUILD_DIR)/serde.o
$(TARGET_DIR)/libserde.a : $(TARGET_DIR) $(BUILD_DIR)/serde.o
	ar crv $(TARGET_DIR)/libserde.a $(BUILD_DIR)/serde.o
install: $(TARGET_DIR)/libserde.a
	if [ ! -d "$(INSTALL_INCLUDE_DIR)" ]; then mkdir $(INSTALL_INCLUDE_DIR); fi
	cp $(SRC_DIR)/serde.hpp $(INSTALL_INCLUDE_DIR)/serde.hpp
	cp $(TARGET_DIR)/libserde.a $(INSTALL_LIB_DIR)/libserde.a
