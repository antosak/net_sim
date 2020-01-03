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

TEST(WorkerTest, create){
    PackageQueue pq(PackageQueueType::FIFO);
    Package pack8;
    pq.push(std::move(pack8));
    std::unique_ptr<PackageQueue> ptr;
    ptr.reset(&pq);
    Worker worker(1, 2, std::move(ptr));
    ASSERT_EQ(1, worker.get_id());
    ASSERT_EQ(ReceiverType::WORKER, worker.get_receiver_type());
}

TEST(StorehouseTest, create){
    PackageQueue pq(PackageQueueType::FIFO);
    Package pack8;
    Package pack9;
    pq.push(std::move(pack8));
    pq.push(std::move(pack9));
    std::unique_ptr<PackageQueue> ptr;
    ptr.reset(&pq);
    Storehouse storehouse(1, std::move(ptr));
    ASSERT_EQ(1, storehouse.get_id());
    ASSERT_EQ(ReceiverType::STOREHOUSE, storehouse.get_receiver_type());
}