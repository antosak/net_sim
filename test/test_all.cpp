//
// Created by MICHAŁ on 11.12.2019.
//

#include "nodes.hpp"
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
    ASSERT_EQ(std::nullopt, ramp.buffer);
    ramp.deliver_goods(1);
    ASSERT_EQ(std::nullopt, ramp.buffer);
    ramp.deliver_goods(2);
    ASSERT_FALSE(std::nullopt == ramp.buffer);
}

TEST(RampTest, send){

}

TEST(WorkerTest, create){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Package pack8;
    ptr_test->push(std::move(pack8));
    Worker worker(1, 2, std::move(ptr_test));
    ASSERT_EQ(1, worker.get_id());
    ASSERT_EQ(ReceiverType::WORKER, worker.get_receiver_type());
}

TEST(WorkerTest, receive){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Worker worker(1, 2, std::move(ptr_test));
    auto n = 4;
    for(auto i = 0; i < n; i++){
        worker.receive_package(Package());
    }
    ASSERT_EQ(worker.size(), n);

}

TEST(StorehouseTest, create){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Package pack8;
    Package pack9;
    ptr_test->push(std::move(pack8));
    ptr_test->push(std::move(pack9));
    Storehouse storehouse(1, std::move(ptr_test));
    ASSERT_EQ(1, storehouse.get_id());
    ASSERT_EQ(ReceiverType::STOREHOUSE, storehouse.get_receiver_type());
}

TEST(StorehouseTest, receive){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    Storehouse storehouse(1, std::move(ptr_test));
    auto n = 4;
    for(auto i = 0; i < n; i++){
        storehouse.receive_package(Package());
    }
    ASSERT_EQ(storehouse.size(), n);
}