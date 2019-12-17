//
// Created by MICHAŁ on 11.12.2019.
//

#ifndef NET_SIM_STORAGE_TYPES_HPP
#define NET_SIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"
#include <list>

enum class PackageQueueType {
    FIFO, LIFO
};

class IPackageStockpile {
public:
    using container = std::list<Package>::const_iterator;
    virtual int size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IPackageStockpile() {};
    virtual void push(Package&& package_) = 0;
    virtual container cbegin() const = 0;
    virtual container cend() const = 0;
    virtual container begin() const = 0;
    virtual container end() const = 0;
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual ~IPackageQueue() {};
    virtual PackageQueueType get_queue_type() const = 0;
    virtual Package&& pop() = 0;
};

class PackageQueue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType type);
    ~PackageQueue(){}; // ?? nadpisuje się dekonstruktor ??
    void push(Package&& package_) override {collection.emplace_back(package_);};
    Package&& pop() override; // nwm jak to..
    PackageQueueType get_queue_type() const override {return Type;};
    bool empty() const override {return collection.empty();};
    int size() const override {return collection.size();};
    container cbegin() const override {return collection.cbegin();};
    container cend() const override {return collection.cend();};
    container begin() const override { return collection.begin();};
    container end() const override {return collection.end();};
private:
    PackageQueueType Type;
    std::list<Package> collection;


};
#endif //NET_SIM_STORAGE_TYPES_HPP