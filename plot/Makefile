CFLAGS = -std=gnu++11 -O2
SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = target
INSTALL_LIB_DIR=/usr/local/lib
INSTALL_INCLUDE_DIR=/usr/local/include/bright_lib/plot
all: $(BUILD_DIR)/axis_range.o $(BUILD_DIR)/base_type.o $(BUILD_DIR)/color.o $(BUILD_DIR)/curve.o $(BUILD_DIR)/figure.o $(BUILD_DIR)/line_style.o

$(TARGET_DIR):
	mkdir $(TARGET_DIR)
$(BUILD_DIR):
	mkdir $(BUILD_DIR) 
$(BUILD_DIR)/axis_range.o : $(BUILD_DIR) $(SRC_DIR)/axis_range.hpp $(SRC_DIR)/axis_range.cpp
	g++ $(SRC_DIR)/axis_range.cpp $(CFLAGS) -c -o $(BUILD_DIR)/axis_range.o
$(BUILD_DIR)/base_type.o : $(BUILD_DIR) $(SRC_DIR)/base_type.hpp $(SRC_DIR)/base_type.cpp
	g++ $(SRC_DIR)/base_type.cpp $(CFLAGS) -c -o $(BUILD_DIR)/base_type.o
$(BUILD_DIR)/color.o : $(BUILD_DIR) $(SRC_DIR)/color.hpp $(SRC_DIR)/color.cpp
	g++ $(SRC_DIR)/color.cpp $(CFLAGS) -c -o $(BUILD_DIR)/color.o
$(BUILD_DIR)/curve.o : $(BUILD_DIR) $(SRC_DIR)/curve.hpp $(SRC_DIR)/curve.cpp
	g++ $(SRC_DIR)/curve.cpp $(CFLAGS) -c -o $(BUILD_DIR)/curve.o
$(BUILD_DIR)/figure.o : $(BUILD_DIR) $(SRC_DIR)/figure.hpp $(SRC_DIR)/figure.cpp
	g++ $(SRC_DIR)/figure.cpp $(CFLAGS) -c -o $(BUILD_DIR)/figure.o
$(BUILD_DIR)/line_style.o : $(BUILD_DIR) $(SRC_DIR)/line_style.hpp $(SRC_DIR)/line_style.cpp
	g++ $(SRC_DIR)/line_style.cpp $(CFLAGS) -c -o $(BUILD_DIR)/line_style.o

$(TARGET_DIR)/libplot.a : $(TARGET_DIR) all
	ar crv $(TARGET_DIR)/libplot.a $(BUILD_DIR)/*.o

install: $(TARGET_DIR)/libplot.a
	if [ ! -d "$(INSTALL_INCLUDE_DIR)" ]; then mkdir $(INSTALL_INCLUDE_DIR); fi
	cp $(SRC_DIR)/*.hpp $(INSTALL_INCLUDE_DIR)
	cp $(TARGET_DIR)/libplot.a $(INSTALL_LIB_DIR)/libplot.a

