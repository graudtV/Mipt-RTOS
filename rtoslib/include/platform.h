#ifndef PLATFORM_H_
#define PLATFORM_H_

#define SUPPORTED_PLATFORMS												\
	"TARGET_*** macro is not set or incorrect. Supported targets: "		\
	"TARGET_LINUX_X86"

#ifdef TARGET_LINUX_X86
	#include <cstddef>
	#include <csignal>
	#include <ucontext.h>

	namespace rt {
		using addr_t = void *;
		using task_id_t = unsigned int;
		using task_stack_sz_t = unsigned int;
		
		class TaskContext {
		private:
			ucontext_t m_uc;
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
		};
	} // rt namespace end
#else
	static_assert(0, SUPPORTED_PLATFORMS);
#endif

#endif // PLATFORM_H_
