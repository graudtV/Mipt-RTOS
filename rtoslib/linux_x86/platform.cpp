#include "platform.h"
#include "kernel_module.h"

void handler(int sig) {
	rt::kernel.relinquish();
}

rt::Timer::Timer(unsigned period) : m_period(period) {
	m_act.sa_handler = handler;
	m_act.sa_flags = SA_RESTART;
	sigemptyset(&m_act.sa_mask);
	sigaction(SIGPROF, &m_act, nullptr);

	m_it.it_interval.tv_sec =    0;
	m_it.it_interval.tv_usec =   m_period; 
	m_it.it_value = m_it.it_interval;
	setitimer(ITIMER_PROF, &m_it, nullptr);
}
