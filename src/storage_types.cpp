//
// Created by MICHAŁ on 11.12.2019.
//
#include "storage_types.hpp"

Package PackageQueue::pop() {
    Package package;
    switch (Type){
        case PackageQueueType::FIFO:
            package = static_cast<Package &&>(collection.front()); // clion wyrzucał tu błąd
            collection.pop_front();
            break;
        case PackageQueueType::LIFO:
            package = static_cast<Package &&>(collection.back());
            collection.pop_back();
            break;
    }
    return package;
}
