#pragma once

#include "config.h"
#include <iostream>
#include <filesystem>

class ConfigParser;

class LibBuilder {
public:
	LibBuilder(ConfigParser *parser,
			const std::filesystem::path& build_path,
			const std::filesystem::path& header_templates,
			const std::filesystem::path& source_templates) :
		m_parser(parser),
		m_build_path(build_path),
		m_header_templates(header_templates),
		m_source_templates(source_templates) {}

	void build();

private:
	ConfigParser *m_parser;
	PlatformConfig m_config;

	std::filesystem::path m_build_path, m_header_templates, m_source_templates;

	void make_rtos_h(std::ostream& os);
	void make_rtos_cpp(std::ostream& os);
	void make_impl_files();
	void make_description_section(std::ostream& os, const std::string& header);
};