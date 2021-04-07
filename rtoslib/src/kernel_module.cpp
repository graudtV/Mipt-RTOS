#include <Mipt-RTOS/kernel_module.h>

namespace rt {

void Kernel::run()
{
	m_current_task = 0;
	m_tasks[0].m_start_from_begining = false;
	m_tasks[0].start();
	//m_tasks[0].abort();
	//relinquish(); // TODO: think if it is OK
}

void Kernel::relinquish()
{
	current_task().save_state();
	while (1) {
		do {
			if (++m_current_task == m_ntasks)
				m_current_task = 0;
		} while (current_task().m_is_suspended == true);
		if (current_task().m_start_from_begining == true) {
			current_task().restart();
			return;
		} else {
			current_task().start();
			return;
		}
	}
}

void Kernel::relinquish(task_id_t task_id)
{
	auto &task = current_task();
	m_current_task = task_id;
	task.next(current_task());
}

} // rt namespace end
