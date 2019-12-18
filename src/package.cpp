#include "package.hpp"

int Package::number_ = 1;

Package::~Package() {
    assigned_IDs.remove(id_);
    freed_IDs.push_back(number_);
    freed_IDs.sort();
}
