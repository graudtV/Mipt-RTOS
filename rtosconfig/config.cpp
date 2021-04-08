#include "config.h"
#include <boost/algorithm/string/predicate.hpp> // case insensitive strings comparison
#include <set>

using namespace std::string_literals;
namespace pt = boost::property_tree;

std::string to_string(Target target)
{
	switch (target) {
	case Target::eLinux_x86:		return "Linux_x86";
	case Target::eLinux_x86_asm:	return "Linux_x86_asm";
	default:						return "Unknown";
	}
}

Target string_to_target(std::string_view name)
{
	Target targets[] = { Target::eLinux_x86, Target::eLinux_x86_asm };

	for (Target target : targets)
		if (boost::iequals(name, to_string(target)))
			return target;
	throw std::invalid_argument(std::string("unkwown target: ") + name.data());
}

void TaskConfig::load_from(pt::ptree& tree)
try {
	name = tree.get<std::string>("name");
	stack_size = tree.get<size_t>("stack_size");
} catch (pt::ptree_bad_path& e) {
	throw std::runtime_error("Task must contain property '"s
		+ e.path<pt::ptree::path_type>().dump() + "'");
}

void ProjectConfig::load_from(pt::ptree& tree)
try {
	target = string_to_target(tree.get<std::string>("Target"));

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

void ProjectConfig::check_correctness()
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