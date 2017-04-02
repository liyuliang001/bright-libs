CFLAGS = -std=gnu++11 -O2
SRC_DIR = src
BUILD_DIR = build
TARGET_DIR = target
INSTALL_LIB_DIR=/usr/local/lib
INSTALL_INCLUDE_DIR=/usr/local/include/bright_lib/hash

install: $(SRC_DIR)/murmur.h
	if [ ! -d "$(INSTALL_INCLUDE_DIR)" ]; then mkdir $(INSTALL_INCLUDE_DIR); fi
	cp $(SRC_DIR)/murmur.h $(INSTALL_INCLUDE_DIR)/murmur.h
