DEFAULT_CONFIG_FILE=config.json

CONFIG_FILE:=$(if $(CONFIG_FILE),$(CONFIG_FILE),$(DEFAULT_CONFIG_FILE))

all: a.out
	
a.out: main.cpp Mipt-RTOS
	c++ -std=c++17 main.cpp Mipt-RTOS/rtos.cpp

Mipt-RTOS:
	rtosconfig $(CONFIG_FILE)

clean:
	rm -rf ./a.out Mipt-RTOS

run: ./a.out
	./a.out
