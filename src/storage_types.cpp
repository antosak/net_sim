//
// Created by MICHAŁ on 11.12.2019.
//
#include "storage_types.hpp"

//PackageQueue::PackageQueue(PackageQueueType type){
////jeżeli dobrze rozumiem to trzeba tu zdefiniowac popfunction w zależności czy lifo czy fifo
//}
//
//PackageQueue::Package&&
Package PackageQueue::pop() {
    Package package;
    switch (Type){
        case PackageQueueType::FIFO:
             package = collection.front();
            collection.pop_front();
            break;
        case PackageQueueType::LIFO:
            package = collection.back();
            collection.pop_back();
            break;
    }
    return package;
}
