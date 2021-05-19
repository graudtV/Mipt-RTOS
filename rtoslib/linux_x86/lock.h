#pragma once
#include "kernel_module.h"

namespace rt {

class Lock {
	bool &m_lock;
public:
	Lock(bool &lock) : m_lock(lock) {
		Timer::pause();
		while (m_lock)
			kernel.relinquish();
		Timer::resume();
		m_lock = true;
	}
	~Lock() {
		m_lock = false;
	}
};
} //namespace rt
