#pragma once

#include <boost/property_tree/ptree.hpp>

struct TaskConfig {
	std::string name;
	size_t stack_size;

	void load_from(boost::property_tree::ptree& tree);
};

struct PlatformConfig {
	std::string platform;
	std::vector<TaskConfig> tasks;

	void load_from(boost::property_tree::ptree& tree);
	void check_correctness();
};