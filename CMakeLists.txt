cmake_minimum_required(VERSION 3.13)
project(net_sim)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(include)

add_executable(net_sim main.cpp src/package.cpp src/factory.cpp src/helpers.cpp src/nodes.cpp src/reports.cpp
        src/simulation.cpp src/types.cpp src/storage_types.cpp)

#==== testy

add_executable(net_sim__test test/test_all.cpp test/main_gtest.cpp src/package.cpp src/factory.cpp src/helpers.cpp src/nodes.cpp src/reports.cpp
        src/simulation.cpp src/types.cpp src/storage_types.cpp test/test_nodes.cpp test/test_Factory.cpp test/test_factory_io.cpp
        test/test_package.cpp test/test_simulate.cpp test/test_storage_types.cpp test/test_reports.cpp)

target_include_directories(net_sim__test PUBLIC
googletest-master/googlemock/include
googletest-master/googletest/include
)

add_subdirectory(googletest-master)

target_link_libraries(net_sim__test gmock)
