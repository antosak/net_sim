#ifndef C___SEMESTR_III_PACKAGE_HPP
#define C___SEMESTR_III_PACKAGE_HPP

#include "types.hpp"
#include <set>
#include <list>

class Package {
public:
    ///Package(ElementID id) : id_(id) {}

    Package() : id_(Package::number_){
        if(freed_IDs.empty()){
            assigned_IDs.push_back(number_);
            Package::number_ += 1;
        }else{
            assigned_IDs.push_back(freed_IDs.front());
        }
    }

    ~Package(){
        assigned_IDs.remove_if(Package::number_);
        freed_IDs.push_back(Package::number_);
        freed_IDs.sort();
    ;}
    ElementID getID() const {return id_;}
private:
    ElementID id_ = 0;
    static int number_;
    static std::list<int> assigned_IDs;
    static std::list<int> freed_IDs;
};
#endif //C___SEMESTR_III_PACKAGE_HPP
