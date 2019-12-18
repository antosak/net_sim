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
    Package pack3;

    EXPECT_EQ(pack1.getID(), pack2.getID() - 1);
    EXPECT_EQ(pack2.getID(), 2);
    EXPECT_EQ(pack3.getID(), 3);
}

TEST(PackTest, creat){
    Package pack1;
}

TEST(PackageTest, overwrite){
    Package pack1;
    Package pack2;
    Package pack3;
//pack2 = pack3;
}