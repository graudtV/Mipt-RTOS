#include "config.h"
#include <set>

using namespace std::string_literals;
namespace pt = boost::property_tree;

void TaskConfig::load_from(pt::ptree& tree)
try {
	name = tree.get<std::string>("name");
	stack_size = tree.get<size_t>("stack_size");
} catch (pt::ptree_bad_path& e) {
	throw std::runtime_error("Task must contain property '"s
		+ e.path<pt::ptree::path_type>().dump() + "'");
}

void PlatformConfig::load_from(pt::ptree& tree)
try {
	platform = tree.get<std::string>("Platform");

	for (auto& task : tree.get_child("Tasks")) {
		TaskConfig task_config;
		task_config.load_from(task.second);
		tasks.push_back(task_config);
	}
	check_correctness();
} catch (pt::ptree_bad_path& e) {
	throw std::runtime_error("Config file must contain property '"s
		+ e.path<pt::ptree::path_type>().dump() + "'");
}

void PlatformConfig::check_correctness()
{
	if (tasks.size() == 0)
		throw std::runtime_error("No tasks specified");
	for (auto& task : tasks) {
		if (task.name.empty())
			throw std::runtime_error("Task with empty name is found");
		if (!(isalpha(task.name[0]) || task.name[0] == '_'))
			throw std::runtime_error("Incorrect task name '"s
				+ task.name + "'. Task names must be C-style identifiers");
	}
	{ /* Check if all tasks have different names */
		std::set<std::string_view> task_names;
		for (auto& task : tasks)
			task_names.insert(task.name);
		if (task_names.size() != tasks.size())
			throw std::runtime_error("Some tasks have equal names");
	}
}