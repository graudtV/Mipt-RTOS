#ifndef PLATFORM_H_
#define PLATFORM_H_

#define SUPPORTED_PLATFORMS												\
	"TARGET_*** macro is not set or incorrect. Supported targets: "		\
	"TARGET_LINUX_X86"

#ifdef TARGET_LINUX_X86
	#include <cstddef>

	namespace rt {

	using addr_t = size_t;
	using task_id_t = unsigned int;
	using task_stack_sz_t = unsigned int;

	} // rt namespace end
#else
	static_assert(0, SUPPORTED_PLATFORMS);
#endif

#endif // PLATFORM_H_