#include "package.hpp"

int Package::number_ = 1;
std::list<int> Package::assigned_IDs;
std::list<int> Package::freed_IDs;

Package::~Package() {
    assigned_IDs.remove(id_);
    freed_IDs.push_back(id_);
    freed_IDs.sort();
}

Package::Package(Package &&package) : id_(package.id_){
    freed_IDs.push_back(package.id_);
    package.id_ = -1;
}

Package::Package() : id_(number_) {
    if (freed_IDs.empty()) {
        assigned_IDs.push_back(number_);
        number_ += 1;
    } else {
        assigned_IDs.push_back(freed_IDs.front());
        freed_IDs.pop_front();
    }
}

void Package::operator = (Package &package ) {
    freed_IDs.push_back(package.id_);
    package.id_ = -1;
}