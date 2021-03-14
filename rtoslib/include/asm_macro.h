#ifndef ASM_MACRO_H_
#define ASM_MACRO_H_

#include <Mipt-RTOS/platform.h>

#ifdef TARGET_LINUX_X86
	#define asm_pushall()			\
		asm volatile (				\
			"push %rax\n\t"			\
			"push %rbx\n\t"			\
			"push %rcx\n\t"			\
			"push %rdx\n\t"			\
		);

	#define asm_popall()

	#define asm_get_stack_pointer()					\
		({											\
			addr_t _sp = 0;							\
			asm ("movq %%rsp, %0" : "=r"(_sp) : );	\
			_sp;									\
		})

	#define asm_set_stack_pointer(sp)				\
		asm ("movq %0, %%rsp" : : "r"((sp)))
#else
	static_assert(0, SUPPORTED_PLATFORMS);
#endif

#endif // ASM_MACRO_H_