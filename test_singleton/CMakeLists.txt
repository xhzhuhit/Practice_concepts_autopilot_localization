cmake_minimum_required(VERSION 2.8)
project(test_singleton)

add_executable(test_singleton src/main.cpp
        src/global_config.cpp)
target_link_libraries(test_singleton dl)
