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
} // testing function written by teachers

TEST(ReceiverPreferencesTest, movingAround){
    Ramp ramp(1, 1);
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Worker worker(1, 2, std::move(ptr_test));
    auto ptr_test_2 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Worker worker_2(2, 2, std::move(ptr_test_2));
    ramp.receiver_preferences_.add_receiver(&worker);
    ASSERT_EQ(ramp.receiver_preferences_.get_preferences().cbegin()->first, &worker);
    ASSERT_EQ(ramp.receiver_preferences_.get_preferences().cbegin()->second, 1);
    ramp.receiver_preferences_.add_receiver((&worker_2));
    ASSERT_EQ(ramp.receiver_preferences_.get_preferences().cbegin()->first, &worker_2);
    ASSERT_EQ(ramp.receiver_preferences_.get_preferences().cbegin()->second, 0.5);
    ramp.receiver_preferences_.remove_receiver(&worker);
    ASSERT_EQ(ramp.receiver_preferences_.get_preferences().cbegin()->first, &worker_2);
    ASSERT_EQ(ramp.receiver_preferences_.get_preferences().cbegin()->second, 1);

} // checking if probability equals one in multiple cases

TEST(RampTest, create){
    Ramp ramp(1, 2);
    ASSERT_EQ(1, ramp.get_id());
    ASSERT_EQ(2, ramp.get_delivery_interval());
} // testing the birth of the ramp

TEST(RampTest, deliverGoods){
    Ramp ramp(1, 2);
    ASSERT_EQ(std::nullopt, ramp.buffer);
    ramp.deliver_goods(1);
    ASSERT_EQ(std::nullopt, ramp.buffer);
    ramp.deliver_goods(2);
    ASSERT_FALSE(std::nullopt == ramp.buffer);
} // testing all the aspects of goods delivering

TEST(RampTest, send){
    Ramp ramp(1, 1);
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Worker worker(1, 2, std::move(ptr_test));
    ramp.receiver_preferences_.add_receiver(&worker);
    ramp.deliver_goods(1);
    ramp.send_package();
    ASSERT_EQ(ramp.buffer, std::nullopt);
} // testing how empty the buffer is after function send_package does its job

TEST(WorkerTest, create){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Package pack8;
    ptr_test->push(std::move(pack8));
    Worker worker(1, 2, std::move(ptr_test));
    ASSERT_EQ(1, worker.get_id());
    ASSERT_EQ(ReceiverType::WORKER, worker.get_receiver_type());
} // the worker itself comes into play

TEST(WorkerTest, receive){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Worker worker(1, 2, std::move(ptr_test));
    auto n = 4;
    for(auto i = 0; i < n; i++){
        worker.receive_package(Package());
    }
    ASSERT_EQ(worker.size(), n);
} // testing weather or not packages disappeared in front of the worker

TEST(WorkerTest, doWork){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Worker worker(1, 2, std::move(ptr_test));
    ASSERT_EQ(std::nullopt, worker.buffer);
    worker.receive_package(Package());
    worker.do_work(1);
    ASSERT_EQ(std::nullopt, worker.buffer);
    worker.do_work(2);
    ASSERT_FALSE(std::nullopt == worker.buffer);
} // worker works just fine

TEST(WorkerTest, send){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Worker worker(1, 2, std::move(ptr_test));
    auto ptr_test_2 = std::make_unique<PackageQueue>(PackageQueueType::LIFO);
    Storehouse storehouse(1, std::move(ptr_test_2));
    worker.receive_package(Package());
    worker.receiver_preferences_.add_receiver(&storehouse);
    ASSERT_TRUE(worker.get_sending_buffer() == std::nullopt);
    worker.do_work(1); // fuck! // w testach zawsze trzeba do_work wywoływać po koleji (z argumentami jako kolejne
    // liczby naturalne) jak się pominie jakąś liczbę to workera szlag trafi (chyba dlatego że przypisujemy pst = t).
    worker.do_work(2);
    ASSERT_FALSE(worker.get_sending_buffer() == std::nullopt);
    worker.send_package();
    ASSERT_TRUE(worker.get_sending_buffer() == std::nullopt);
    ASSERT_EQ(worker.buffer, std::nullopt);
    ASSERT_EQ(storehouse.size(), 1);

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
} // storehouse shall be full of resources soon, so far it exists

TEST(StorehouseTest, receive){
    auto ptr_test = std::make_unique<PackageQueue>(PackageQueueType::FIFO);
    Storehouse storehouse(1, std::move(ptr_test));
    auto n = 4;
    for(auto i = 0; i < n; i++){
        storehouse.receive_package(Package());
    }
    ASSERT_EQ(storehouse.size(), n);
} // and receives packages correctly
