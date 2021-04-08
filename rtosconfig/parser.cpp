#include "parser.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

PlatformConfig JsonParser::parse()
{
	pt::ptree tree;
	PlatformConfig config;

	pt::read_json(m_input_stream, tree);
	config.load_from(tree);
	return config;
}