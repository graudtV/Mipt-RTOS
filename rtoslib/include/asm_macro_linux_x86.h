#pragma once

#include "platform.h"

#define asm_pushall()			\
	asm volatile (				\
		"push %rax\n\t"			\
		"push %rbx\n\t"			\
		"push %rcx\n\t"			\
		"push %rdx\n\t"			\
		"push %rsi\n\t"			\
		"push %rdi\n\t"			\
		"push %rbp\n\t"			\
	);


#define asm_popall()			\
	asm volatile (				\
		"pop %rbp\n\t"			\
		"pop %rdi\n\t"			\
		"pop %rsi\n\t"			\
		"pop %rdx\n\t"			\
		"pop %rcx\n\t"			\
		"pop %rbx\n\t"			\
		"pop %rax\n\t"			\
	);

#define asm_get_stack_pointer()							\
	({													\
		addr_t _sp = 0;									\
		asm volatile ("movq %%rsp, %0" : "=r"(_sp) : );	\
		_sp;											\
	})

#define asm_set_stack_pointer(sp)	\
	asm volatile ("movq %0, %%rsp" : : "r"((sp)) : "rsp")
