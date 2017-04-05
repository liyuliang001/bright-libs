INSTALL_INCLUDE_DIR=/usr/local/include/bright_lib
$(INSTALL_INCLUDE_DIR):
	mkdir $(INSTALL_INCLUDE_DIR)
install : $(INSTALL_INCLUDE_DIR)
	make install -C serializer-deserializer
	make install -C network
	make install -C plot
	make install -C hash
	make install -C types
	make install -C tcp_socket
