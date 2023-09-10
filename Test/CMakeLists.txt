cmake_minimum_required(VERSION 3.15)

project(TestPRNG)

set(CMAKE_CXX_STANDARD 17)

add_executable(TestPRNG "test.cpp")

target_link_libraries(TestPRNG PRIVATE OS::PRNG)