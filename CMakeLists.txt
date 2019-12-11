cmake_minimum_required(VERSION 3.13)
project(net_sim)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -Wpedantic -pedantic-errors)

include_directories(
        include
)

add_executable(net_sim main.cpp src/package.cpp src/factory.cpp src/helpers.cpp src/nodes.cpp src/reports.cpp src/simulation.cpp src/types.cpp src/storage_types.cpp)

#==============================

set(SOURCES_FILES_TESTS
        test/test_all.cpp test/gtest_main.cpp)

add_executable(net_sim__test ${SOURCE_FILES} ${SOURCES_FILES_TESTS} test/gtest_main.cpp)

# TODO: Poniższe ścieżki prawdopodobnie musisz zmienić...
target_include_directories(net_sim__test PUBLIC
googletest-master/googlemock/include
googletest-master/googletest/include
)

# TODO: Poniższą ścieżkę prawdopodobnie musisz zmienić...
add_subdirectory(googletest-master googletest-master)

target_link_libraries(net_sim__test gmock)