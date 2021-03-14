all: a.out
	
a.out: main.cpp rtos.cpp rtos.h
	c++ main.cpp -std=c++17 rtos.cpp -DTARGET_LINUX_X86 /usr/local/lib/Mipt-RTOS/*

rtos.h rtos.cpp: config.json
	rtosconfig config.json

clean:
	rm rtos.h rtos.cpp

run: ./a.out
	./a.out
