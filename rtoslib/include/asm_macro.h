#ifndef ASM_LINUX_X86_H_
#define ASM_LINUX_X86_H_

#include "rtos/user_platform.h"

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
	

#endif // ASM_LINUX_X86_H_