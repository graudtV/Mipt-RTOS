#pragma once

#include <cstddef>
#include <csignal>
#include <ucontext.h>
#include <sys/time.h>

namespace rt {

using addr_t = void *;
using task_id_t = unsigned int;
using task_stack_sz_t = unsigned int;

class TaskContext {
public:
	TaskContext(void (*routine_address) (), addr_t stack_addr, task_stack_sz_t stack_size) {
		getcontext(&m_uc); //TODO possible error;
		m_uc.uc_stack.ss_sp = stack_addr;
		m_uc.uc_stack.ss_size = stack_size;
		m_uc.uc_link = nullptr;
		sigemptyset(&m_uc.uc_sigmask);
		makecontext(&m_uc, routine_address, 0);
	}
	void set() const {
		setcontext(&m_uc);
	}
	void get() {
		getcontext(&m_uc);
	}
	void swap(const TaskContext &next) {
		swapcontext(&m_uc, &next.m_uc);
	}
private:
	ucontext_t m_uc;
};

class Timer {
private:
	using HandlerFptr = void (*) (int);
	Timer(unsigned period);
	struct sigaction m_act;
	struct itimerval m_it;
	unsigned m_period;
	static Timer m_only_one;
public:
	~Timer() = default;
	Timer(const Timer &) = delete;
	Timer &operator =(const Timer &) = delete;
	static constexpr Timer& get_instance() {
		return m_only_one;
	}
};

inline constexpr Timer& timer = Timer::get_instance();

} // rt namespace end
