cmake_minimum_required(VERSION 3.10)

project(Mipt-RTOS)

add_subdirectory(rtosconfig)

install(DIRECTORY rtoslib DESTINATION lib)