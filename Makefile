.PHONY: all build install uninstall clean

all: build

build: rtosconfig/build/rtosconfig

install: build
	chmod +x ./install.sh && ./install.sh

uninstall:
	chmod +x ./install.sh && ./install.sh -u

# cleans build directories
clean:
	rm -rf rtosconfig/build

rtosconfig/build/rtosconfig: rtosconfig/main.cpp
	mkdir -p rtosconfig/build
	$(CXX) $(CXXFLAGS) $^ -o $@
