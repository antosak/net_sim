#ifndef C___SEMESTR_III_PACKAGE_HPP
#define C___SEMESTR_III_PACKAGE_HPP

#include "types.hpp"
#include <set>
#include <list>
#include <algorithm>

class Package {
public:
    Package(Package &&package);
    Package();
    ~Package();

    ElementID get_id() const { return id_;}

    void operator = (Package &package );

private:
    ElementID id_ = 0;
    static int number_;
    static std::list<int> assigned_IDs;
    static std::list<int> freed_IDs;
};

#endif //C___SEMESTR_III_PACKAGE_HPP
