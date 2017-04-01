CFLAGS = -std=gnu++11 -O2
SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = target
INSTALL_LIB_DIR=/usr/local/lib
INSTALL_INCLUDE_DIR=/usr/local/include/bright_lib/types

install: $(SRC_DIR)/bigint.hpp
	if [ ! -d "$(INSTALL_INCLUDE_DIR)" ]; then mkdir $(INSTALL_INCLUDE_DIR); fi
	cp $(SRC_DIR)/bigint.hpp $(INSTALL_INCLUDE_DIR)/bigint.hpp
