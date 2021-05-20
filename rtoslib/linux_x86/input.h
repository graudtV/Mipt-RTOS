#pragma once
#include <iostream>
#include "lock.h"

namespace rt {

class Input {
	bool m_lock = false;
	static Input m_only_one;
	Input(){}
public:
	template <typename... Ts>
	void read(Ts&... obj) {
		auto lock = Lock{m_lock};
		(std::cin >> ... >> obj);
	}
	static constexpr Input& get_instance() {
		return m_only_one;
	}
};
inline constexpr Input& input = Input::get_instance();
}
