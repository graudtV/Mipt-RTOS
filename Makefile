.PHONY: all build install uninstall clean

all: build

build: config_parser/build/rtosconfig

install: build
	chmod +x ./install.sh && ./install.sh

uninstall:
	chmod +x ./install.sh && ./install.sh -u

# cleans build directories
clean:
	rm -rf config_parser/build

config_parser/build/rtosconfig: config_parser/main.cpp
	mkdir -p config_parser/build
	$(CXX) $(CXXFLAGS) $^ -o $@
