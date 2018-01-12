SOCKETIO_CLIENT_CPP_BUILD_DIR = ../../socket.io-client-cpp/build

.PHONY: clean all
all: main

main.o: main.cpp
	g++ -std=c++11 -c -I$(SOCKETIO_CLIENT_CPP_BUILD_DIR)/include $< -o $@

main: main.o not_fair.o
	g++ $< not_fair.o $(SOCKETIO_CLIENT_CPP_BUILD_DIR)/lib/Release/*a -lboost_system -lpthread -o $@ # maybe make this -static

not_fair.o: not_fair.cpp
	g++ -std=c++11 -c -I$(SOCKETIO_CLIENT_CPP_BUILD_DIR)/include $< -o $@

clean:
	rm main main.o not_fair.o
