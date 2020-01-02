//
// Created by MICHAŁ on 11.12.2019.
//

#include <nodes.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "package.hpp"


TEST(simpleTest, sub){
    EXPECT_EQ(2, 4 - 2);
}

TEST(PackageTest, create){
    Package pack1;
    Package pack2;
    Package pack3;

    EXPECT_EQ(pack1.get_id(), pack2.get_id() - 1);
    EXPECT_EQ(pack2.get_id(), 2);
    EXPECT_EQ(pack3.get_id(), 3);
}


TEST(PackageTest, overwrite){
    Package pack1;
    Package pack2;
    Package pack3;
    Worker work1;
    Worker work2;
}