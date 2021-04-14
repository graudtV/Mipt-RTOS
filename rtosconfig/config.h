#pragma once

#include <boost/property_tree/ptree.hpp>

enum class Target { eLinux_x86, eLinux_x86_asm };

std::string to_string(Target target);
Target string_to_target(std::string_view name);

struct TaskConfig {
	std::string name;
	size_t stack_size;

	void load_from(boost::property_tree::ptree& tree);
};

struct ProjectConfig {
	Target target;
	std::vector<TaskConfig> tasks;

	void load_from(boost::property_tree::ptree& tree);
	void check_correctness();
};