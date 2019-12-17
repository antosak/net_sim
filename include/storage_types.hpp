//
// Created by MICHAŁ on 11.12.2019.
//

#ifndef NET_SIM_STORAGE_TYPES_HPP
#define NET_SIM_STORAGE_TYPES_HPP

#include "types.hpp"
#include "package.hpp"

enum class PackageQueueType {
    FIFO, LIFO
};

class IPackageStockpile {
public:
    virtual int size() const = 0;
    virtual bool empty() const = 0;
    virtual ~IPackageStockpile() {}; // zzawsze trzeba dekonstruktor czy nie?
    virtual void push(Package&& package_) = 0;
    // jeszcze trzeba napisać cytuję:: "metody pozwalające na uzyskanie dostępu “tylko do odczytu” do kontenera
    // przechowującego półprodukty (tj. metody [c]begin(), [c]end() – łącznie 4 metody)",
    // ale nie bardzo wiem jak
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual ~IPackageQueue() {};
    virtual PackageQueueType get_queue_type() const = 0;
    virtual Package&& pop() = 0;
};

class PackageQueue : public IPackageQueue {
public:

private:
    PackageQueueType Type;


};
#endif //NET_SIM_STORAGE_TYPES_HPP
