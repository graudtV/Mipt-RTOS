#pragma once

#include "config.h"

#include <string>
#include <vector>
#include <iostream>

class ConfigParser {
public:
	ConfigParser(std::istream& is) : m_input_stream(is) {}

	virtual ProjectConfig parse() = 0;

protected:
	std::istream& m_input_stream;
};

class JsonParser : public ConfigParser {
public:
	JsonParser(std::istream& is) : ConfigParser(is) {}

	ProjectConfig parse() override;
};