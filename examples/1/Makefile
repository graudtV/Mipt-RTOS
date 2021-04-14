all: a.out
	
a.out: main.cpp Mipt-RTOS
	c++ -std=c++17 main.cpp Mipt-RTOS/rtos.cpp

Mipt-RTOS:
	rtosconfig config.json

clean:
	rm -rf ./a.out Mipt-RTOS

run: ./a.out
	./a.out
