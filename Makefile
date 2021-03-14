.PHONY: all build install uninstall clean
EXTRA_CXXFLAGS=-std=c++17 -Wall -Wextra

all: build

build: rtosconfig/build/rtosconfig

install: build
	chmod +x ./install.sh && sudo bash install.sh

uninstall:
	chmod +x ./install.sh && sudo bash install.sh -u

# cleans build directories
clean:
	rm -rf rtosconfig/build

rtosconfig/build/rtosconfig: rtosconfig/main.cpp
	mkdir -p rtosconfig/build
	$(CXX) $(EXTRA_CXXFLAGS) $(CXXFLAGS) $^ -o $@
