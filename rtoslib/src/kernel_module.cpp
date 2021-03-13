#include "rtos/module/kernel_module.h"
#include "rtos/user_platform.h"
#include ASSEMBLER_HEADER_NAME

namespace rt {

Kernel::Kernel()
{
	task_id_t task_id;
	addr_t sp = asm_get_stack_pointer();

	for (task_id = 0; task_id < m_ntasks; ++task_id) {
		m_stack_begin[task_id] = sp;
		sp -= m_task_stack_sizes[task_id];
		//m_start_from_begining
	}

}

void Kernel::run()
{

}

void Kernel::relinquish()
{

}

} // rt namespace end