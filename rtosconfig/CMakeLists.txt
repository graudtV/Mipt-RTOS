cmake_minimum_required(VERSION 3.10)

project(rtosconfig)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED)

add_executable(rtosconfig)

target_include_directories(rtosconfig PRIVATE include)

target_sources(rtosconfig PRIVATE
	src/main.cpp
	src/config.cpp
	src/lib_builder.cpp
	src/parser.cpp
	)

install(TARGETS rtosconfig DESTINATION bin)