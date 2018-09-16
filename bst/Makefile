CFLAGS = -std=gnu++11 -O3
SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = target
INSTALL_LIB_DIR=/usr/local/lib
INSTALL_INCLUDE_DIR=/usr/local/include/bright_lib/bst

install: $(SRC_DIR)/bst.hpp
	if [ ! -d "$(INSTALL_INCLUDE_DIR)" ]; then mkdir $(INSTALL_INCLUDE_DIR); fi
	cp $(SRC_DIR)/bst.hpp $(INSTALL_INCLUDE_DIR)/bst.hpp
