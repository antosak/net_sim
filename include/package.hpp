#ifndef C___SEMESTR_III_PACKAGE_HPP
#define C___SEMESTR_III_PACKAGE_HPP

#include "types.hpp"
#include <set>
#include <list>
#include <algorithm>

class Package {
public:
    Package(ElementID id) : id_(id) {
        bool already_assigned = (std::find(assigned_IDs.begin(), assigned_IDs.end(), id) != assigned_IDs.end());
        if (already_assigned)
            throw std::invalid_argument("Given ID is already in use!");
        assigned_IDs.push_back(id);
    }

    Package() : id_(Package::number_) {
        if (freed_IDs.empty()) {
            assigned_IDs.push_back(number_);
            Package::number_ += 1;
        } else {
            assigned_IDs.push_back(freed_IDs.front());
            freed_IDs.pop_front();
        }
    }

    ~Package() {
        assigned_IDs.remove(id_);
        freed_IDs.push_back(Package::number_);
        freed_IDs.sort();
    }

    ElementID getID() const { return id_; }

private:
    ElementID id_ = 0;
    static int number_;
    std::list<int> assigned_IDs;
    std::list<int> freed_IDs;
};

#endif //C___SEMESTR_III_PACKAGE_HPP
