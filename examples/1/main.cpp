#include "rtos.h"
#include <iostream>

decltask(task1)
{
	printf("task1 --- point 0\n"); kernel.relinquish();
	task2.suspend();
	printf("task1 --- point 1\n"); kernel.relinquish();
	printf("task1 --- point 2\n"); kernel.relinquish();
	printf("task1 --- point 3\n"); kernel.relinquish();
	task1.suspend();
	task2.resume();
	kernel.relinquish();
}

decltask(task2)
{
	printf("task2 --- point 0\n"); kernel.relinquish();
	printf("task2 --- point 1\n"); kernel.relinquish();
	printf("task2 --- point 2\n"); kernel.relinquish();
	printf("task2 --- point 3\n"); kernel.relinquish();
}

int main()
{
	printf("--- started ---\n");
	rt::kernel.run();
	printf("--- finished ---\n");


	return 0;
}
