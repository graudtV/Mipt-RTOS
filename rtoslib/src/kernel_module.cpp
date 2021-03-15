#include <Mipt-RTOS/kernel_module.h>
#include <Mipt-RTOS/asm_macro.h>

#include <iostream>

namespace rt {

void Kernel::run()
{
	/*  Declaring task_id before sp variable (i.e. outside loop) in order not
	 * to change sp after it was acquired. Actually, it shouldn't influence anything,
	 * but in such way it seems more explicit */
	task_id_t task_id;
	addr_t sp = asm_get_stack_pointer();

	for (task_id = 0; task_id < m_ntasks; ++task_id) {
		m_tasks[task_id].m_stack_starting = sp;
		sp -= m_tasks[task_id].m_stack_size;
		/* m_tasks[task_id].m_start_from_begining = true automatically */
		/* m_tasks[task_id].m_is_suspended = false automatically */
	}

	m_current_task = 0;
	m_tasks[0].m_start_from_begining = false;
	m_tasks[0].m_routine_address();
	m_tasks[0].abort();
	relinquish(); // TODO: think if it is OK
}

void Kernel::relinquish()
{
	asm_pushall();
	current_task().m_stack_pointer = asm_get_stack_pointer();

	while (1) {
		do {
			if (++m_current_task == m_ntasks)
				m_current_task = 0;
		} while (current_task().m_is_suspended == true);
		if (current_task().m_start_from_begining == true) {
			current_task().m_start_from_begining = false;
			asm_set_stack_pointer(current_task().m_stack_starting);
			current_task().m_routine_address();
			current_task().abort();
		} else {
			asm_set_stack_pointer(current_task().m_stack_pointer);
			asm_popall();
			return;
		}
	}
}

} // rt namespace end