#pragma once

#include "config.h"
#include <iostream>
#include <filesystem>
#include <map>

class ConfigParser;

class LibBuilder {
public:
	LibBuilder(ConfigParser *parser,
			const std::filesystem::path& build_path,
			const std::filesystem::path& lib_path) :
		m_parser(parser),
		m_build_path(build_path),
		m_lib_path(lib_path) {}

	void build();

private:
	ConfigParser *m_parser;
	ProjectConfig m_config;

	std::filesystem::path m_build_path, m_lib_path;

	void make_rtos_h(std::ostream& os);
	void make_rtos_cpp(std::ostream& os);
	void make_impl_files();
	void make_description_section(std::ostream& os, const std::string& header);

	using Filemap = std::map<std::string, std::string>;

	static Filemap common_filemap;
	static Filemap linux_x86_filemap;
	static Filemap linux_x86_asm_filemap;

	void copy_files(const std::filesystem::path& src_root, const std::filesystem::path& dst_root, const Filemap& filemap);
};