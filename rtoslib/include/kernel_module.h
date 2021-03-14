#ifndef RTOS_KERNEL_MODULE_H_
#define RTOS_KERNEL_MODULE_H_

#include <Mipt-RTOS/platform.h>

namespace rt {

using PfnTaskRouting = void (*) (void);

class Kernel final {
public:
	static Kernel& get_instance() { static Kernel only_one; return only_one; }

	void run();
	void relinquish();
	void suspend() { suspend_task(m_current_task); }

	void suspend_task(task_id_t task_id) { m_task_is_suspended[task_id] = true; }
	void resume_task(task_id_t task_id) { m_task_is_suspended[task_id] = false; }
	void abort_task(task_id_t task_id) { m_task_is_suspended[task_id] = m_task_start_from_begining[task_id] = true; }
	// void restart_task(task_id_t task_id) {}
	// void reset_task(task_id_t task_id);
	/* ... */
private:
	Kernel();
	~Kernel() {}
	Kernel(const Kernel& other) = delete;
	Kernel(Kernel&& other) = delete;
	Kernel& operator =(const Kernel& other) = delete;
	Kernel& operator =(Kernel&& other) = delete;

	static const int m_ntasks;
	static const PfnTaskRouting m_task_routine_addresses[];
	static task_stack_sz_t m_task_stack_sizes[];
	static addr_t m_task_stack_pointers[];
	static addr_t m_task_stack_starting[];
	static bool m_task_start_from_begining[];
	static bool m_task_is_suspended[];

	static task_id_t m_current_task;
};

inline Kernel& kernel = Kernel::get_instance();

} // rt namespace end

#endif // RTOS_KERNEL_MODULE_H_