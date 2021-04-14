#pragma once

#include "platform.h"

namespace rt {

using PfnTaskRouting = void (*) (void);

class Task final {
public:
	Task(const Task& other) = delete;
	Task(Task&& other) = delete;
	Task& operator =(const Task& other) = delete;
	Task& operator =(Task&& other) = delete;

	/* User API for managing tasks */
	void suspend() { m_is_suspended = true; }
	void resume() { m_is_suspended = false; }
	void abort() { m_is_suspended = m_start_from_begining = true; }

	bool is_suspended() const { return m_is_suspended; }
	bool is_aborted() const { return m_is_suspended == true && m_start_from_begining == true; }

private:
	PfnTaskRouting m_routine_address = nullptr;
	task_stack_sz_t m_stack_size = 0;
	addr_t m_stack_pointer = 0;
	addr_t m_stack_starting = 0;
	bool m_start_from_begining = true;
	bool m_is_suspended = false;

	friend class Kernel;

	/* Library will create tasks itself, you do not need to create them manually */
	Task(PfnTaskRouting routine_address, task_stack_sz_t stack_size) :
		m_routine_address(routine_address),
		m_stack_size(stack_size) {}
};

class Kernel final {
public:
	static constexpr Kernel& get_instance() { return m_only_one; }

	void run();
	void relinquish();
	void suspend() { current_task().suspend(); }

	task_id_t ntasks() const { return m_ntasks; }
	Task& task(task_id_t task_id) { return m_tasks[task_id]; }
	Task& current_task() { return m_tasks[m_current_task]; }

private:
	Kernel() {}
	~Kernel() {}
	Kernel(const Kernel& other) = delete;
	Kernel(Kernel&& other) = delete;
	Kernel& operator =(const Kernel& other) = delete;
	Kernel& operator =(Kernel&& other) = delete;

	static Kernel m_only_one;
	static const task_id_t m_ntasks;
	static Task m_tasks[];
	static task_id_t m_current_task;
};

inline constexpr Kernel& kernel = Kernel::get_instance();

} // rt namespace end