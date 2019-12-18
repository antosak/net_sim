#include "package.hpp"

int Package::number_ = 1;
std::list<int> Package::assigned_IDs;
std::list<int> Package::freed_IDs;

Package::~Package() {
    assigned_IDs.remove(id_);
    freed_IDs.push_back(id_);
    freed_IDs.sort();
}
