#pragma once
#include <iostream>
#include "lock.h"

namespace rt {

class Output {
	bool m_lock = false;
	static Output m_only_one;
	Output(){}
public:
	template <typename... Ts>
	void write(const Ts&... obj) {
		auto lock = Lock{m_lock};
		(std::cout << ... << obj);
	}
	static constexpr Output& get_instance() {
		return m_only_one;
	}
};
inline constexpr Output& output = Output::get_instance();
}
