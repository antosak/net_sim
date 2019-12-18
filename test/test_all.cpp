//
// Created by MICHAŁ on 11.12.2019.
//

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "package.hpp"


TEST(simpleTest, sub){
    EXPECT_EQ(2, 4 - 2);
}

TEST(PackageTest, create){
    Package pack1;
    Package pack2;

    EXPECT_EQ(pack1.getID(), pack2.getID() - 1);
}