#include <Mipt-RTOS/kernel_module.h>
#include <Mipt-RTOS/asm_macro.h>

namespace rt {

Kernel::Kernel()
{
	task_id_t task_id;
	addr_t sp = asm_get_stack_pointer();

	for (task_id = 0; task_id < m_ntasks; ++task_id) {
		m_task_stack_starting[task_id] = sp;
		sp -= m_task_stack_sizes[task_id];
		/* m_task_start_from_begining[task_id] = true automatically */
		/* m_task_is_suspended[task_id] = false automatically */
	}
}

void Kernel::run()
{
	m_task_start_from_begining[0] = false;
	m_current_task = 0;
	m_task_routine_addresses[0] ();
	abort_task(0);
	relinquish(); // TODO: think if it is OK
}

void Kernel::relinquish()
{
	asm_pushall();
	m_task_stack_pointers[m_current_task] = asm_get_stack_pointer();

	while (1) {
		do {
			if (++m_current_task == m_ntasks)
				m_current_task = 0;
		} while (m_task_is_suspended[m_current_task] == true);
		if (m_task_start_from_begining[m_current_task] == true) {
			m_task_start_from_begining[m_current_task] = false;
			asm_set_stack_pointer(m_task_stack_starting[m_current_task]);
			m_task_routine_addresses[m_current_task] ();
			abort_task(m_current_task);
		} else {
			asm_set_stack_pointer(m_task_stack_pointers[m_current_task]);
			asm_popall();
			return;
		}
	}
}

} // rt namespace end