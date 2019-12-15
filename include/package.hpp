#ifndef C___SEMESTR_III_PACKAGE_HPP
#define C___SEMESTR_III_PACKAGE_HPP


#include "types.hpp"

class Package {
public:
    Package(ElementID id) : id_(id) {}
    Package() : id_(Package::number_){Package::number_ += 1;}
    ElementID getID() const {return id_;}
private:
    ElementID id_ = 0;
    static int number_;
};
#endif //C___SEMESTR_III_PACKAGE_HPP
