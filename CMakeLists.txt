cmake_minimum_required(VERSION 3.22)
project(FileSearch)
add_executable(search main.cpp file_search.cpp)
install(TARGETS search DESTINATION bin)