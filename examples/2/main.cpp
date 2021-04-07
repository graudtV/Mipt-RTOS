#include "rtos.h"
#include <iostream>
#include <signal.h>
#include <sys/time.h>

void tick(int sig, siginfo_t *info, void *ctxt) {
	std::cout << "tick" << std::endl;
	kernel.relinquish(0);
}


decltask(scheduler)
{
	static rt::task_id_t i = 1;
	if (i == rt::kernel.ntasks())
		i = 1;
	std::cerr << i << std::endl;
	kernel.set_task(i++);
}

decltask(task1)
{
	while (true)
		;
		//printf("task1 --- point 0\n");
}

decltask(task2)
{
	while (true)
		;
		//printf("task2 --- point 0\n");
}

int main()
{
	struct sigaction act;
        act.sa_sigaction = tick;
        act.sa_flags = SA_RESTART | SA_SIGINFO;
        sigemptyset(&act.sa_mask);
        sigaction(SIGALRM, &act, nullptr);

        struct itimerval timtick;
        timtick.it_interval.tv_sec =    0;
        timtick.it_interval.tv_usec =   10000; 
        timtick.it_value = timtick.it_interval;
        setitimer(ITIMER_REAL, &timtick, nullptr);

	printf("--- started ---\n");
	rt::kernel.run();
	printf("--- finished ---\n");


	return 0;
}
