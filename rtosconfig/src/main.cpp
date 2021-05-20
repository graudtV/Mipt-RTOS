#include "lib_builder.h"
#include "parser.h"
#include <fstream>

using namespace std::string_literals;

int main(int argc, char *argv[])
try {
	const char *config_file_name = nullptr;
	std::filesystem::path build_path("Mipt-RTOS");
	std::filesystem::path lib_path("/usr/local/src/Mipt-RTOS");

	if (argc != 2) {
		std::cerr << "Usage: rtosconfig config_file_name.json" << std::endl;
		return EXIT_FAILURE;	
	}
	config_file_name = argv[1];

	std::ifstream fin(config_file_name);
	if (!fin)
		throw std::runtime_error("cannot open file '"s + config_file_name + "'");

	JsonParser parser(fin);
	LibBuilder builder(&parser, build_path, lib_path);
	builder.build();
} catch (std::exception& e) {
	std::cerr << "Configuration failure: " << e.what() << std::endl;
	return EXIT_FAILURE;
}
