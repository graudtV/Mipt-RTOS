#include "lib_builder.h"
#include "parser.h"
#include <fstream>

using namespace std::string_literals;

int main(int argc, char *argv[])
try {
	const char *config_file_name = nullptr;
	std::filesystem::path build_dir("Mipt-RTOS");
	std::filesystem::path headers_dir("/usr/local/include/Mipt-RTOS");
	std::filesystem::path sources_dir("/usr/local/src/Mipt-RTOS");

	if (argc != 2) {
		std::cerr << "Usage: rtosconfig config_file_name.json" << std::endl;
		return EXIT_FAILURE;	
	}
	config_file_name = argv[1];

	std::ifstream fin(config_file_name);
	if (!fin)
		throw std::runtime_error("cannot open file '"s + config_file_name + "'");

	JsonParser parser(fin);
	LibBuilder builder(&parser, build_dir, headers_dir, sources_dir);
	builder.build();

} catch (std::exception& e) {
	std::cerr << "Configuration failure: " << e.what() << std::endl;
	return EXIT_FAILURE;
}
