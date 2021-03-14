#include "rtos.h"
#include <iostream>

decltask(task1)
{
	printf("task1!\n");
}

decltask(task2)
{
	printf("task2!\n");
}

int main()
{
	printf("--- started ---\n");
	rt::kernel.run();
	printf("--- finished ---\n");


	return 0;
}