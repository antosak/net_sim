// 35: Michał Antos (302815), Szymon Brożyna (309040)
#ifndef NET_SIM_STORAGE_TYPES_HPP
#define NET_SIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"
#include "helpers.hpp"

#include <list>

enum class PackageQueueType {
    FIFO, LIFO
};

class IPackageStockpile {
public:
    using const_iterator = std::list<Package>::const_iterator;
    virtual int size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IPackageStockpile() {};
    virtual void push(Package&& package_) = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator cend() const = 0;
    virtual const_iterator begin() const = 0;
    virtual const_iterator end() const = 0;
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual ~IPackageQueue() {};
    virtual PackageQueueType get_queue_type() const = 0;
    virtual Package pop() = 0;
};

class PackageQueue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType type = PackageQueueType::LIFO) : Type(type){}
    ~PackageQueue(){};
    void push(Package&& package_) override {collection.emplace_back(std::move(package_));};
    Package pop() override;
    PackageQueueType get_queue_type() const override {return Type;};
    bool empty() const override {return collection.empty();};
    int size() const override {return collection.size();};
    const_iterator cbegin() const override {return collection.cbegin();};
    const_iterator cend() const override {return collection.cend();};
    const_iterator begin() const override { return collection.cbegin();};
    const_iterator end() const override {return collection.cend();};
private:
    const PackageQueueType Type;
    std::list<Package> collection;
};

#endif //NET_SIM_STORAGE_TYPES_HPP
