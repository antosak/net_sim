cmake_minimum_required(VERSION 3.13)
project(net_sim)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

add_executable(net_sim main.cpp src/factory.cpp src/helpers.cpp src/nodes.cpp src/reports.cpp src/simulation.cpp src/types.cpp src/storage_types.cpp)

