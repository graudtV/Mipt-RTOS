#ifndef RTOS_TASK_MODULE_H_
#define RTOS_TASK_MODULE_H_

#include <Mipt-RTOS/kernel_module.h>

namespace rt {

class Task final {
public:
	constexpr Task(task_id_t task_id) noexcept : m_task_id(task_id) {}

	void suspend() const { kernel.suspend_task(m_task_id); }
	void resume() const { kernel.resume_task(m_task_id); }

private:
	int m_task_id;
};

} // rt namespace end

#endif // RTOS_TASK_MODULE_H_