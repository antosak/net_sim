//
// Created by MICHAŁ on 11.12.2019.
//
#include <gtest/gtest.h>
#include "test_all.cpp"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}