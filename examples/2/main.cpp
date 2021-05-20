#include "rtos.h"
#include <iostream>
#include <signal.h>
#include <sys/time.h>

decltask(task1)
{
	while (true)
		printf("task1\n");
}

decltask(task2)
{
	while (true)
		printf("task2\n");
}

int main()
{
	rt::kernel.run();
}
