// 35: Michał Antos (302815), Szymon Brożyna (309040)
#include "storage_types.hpp"

Package PackageQueue::pop() {
    Package package;
    switch (Type){
        case PackageQueueType::FIFO:
            package = std::move(collection.front());
            collection.pop_front();
            break;
        case PackageQueueType::LIFO:
            package = std::move(collection.back());
            collection.pop_back();
            break;
    }
    return package;
}
