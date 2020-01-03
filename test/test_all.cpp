//
// Created by MICHAŁ on 11.12.2019.
//

#include <nodes.hpp>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "package.hpp"
#include "storage_types.hpp"

TEST(PackageTest, create){
    Package pack1;
    Package pack2;
    Package pack3;

    EXPECT_EQ(pack1.get_id(), pack2.get_id() - 1);
    EXPECT_EQ(pack2.get_id(), 2);
    EXPECT_EQ(pack3.get_id(), 3);
}

TEST(RampTest, create){
    Ramp ramp(1, 2);
    ASSERT_EQ(1, ramp.get_id());
    ASSERT_EQ(2, ramp.get_delivery_interval());
}

TEST(RampTest, deliver_goods){
    Ramp ramp(1, 2);
    ASSERT_EQ(nullptr, ramp.buffer); //żeby test przechodził buffer zmieniłem na publiczny publiczny
    ramp.deliver_goods(1);
    ASSERT_EQ(nullptr, ramp.buffer);
    ramp.deliver_goods(2);
    ASSERT_FALSE(nullptr == ramp.buffer);
}

TEST(WorkerTest, create){
    PackageQueue pq(PackageQueueType::FIFO);
    std::unique_ptr<PackageQueue> ptr;
    Worker worker(1, 2, ptr); //trzeba nadpisac te metode...
    ASSERT_EQ(1, worker.get_id());
    ASSERT_EQ(ReceiverType::WORKER, worker.get_receiver_type());
}

TEST(StorehouseTest, create){
    std::unique_ptr<IPackageStockpile> ptr;
    Storehouse storehouse(1, ptr); //to samo co w workerze
    ASSERT_EQ(1, storehouse.get_id());
    ASSERT_EQ(ReceiverType::STOREHOUSE, storehouse.get_receiver_type());
}