//
// Created by MICHAŁ on 11.12.2019.
//

#ifndef NET_SIM_NODES_HPP
#define NET_SIM_NODES_HPP

#include <map>
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include <vector>
#include <memory>

enum class ReceiverType {
    WORKER, STOREHOUSE
};

class IPackageReceiver {
public:
    virtual ~IPackageReceiver(){};
    virtual void receive_package(Package&& p) = 0;
    virtual ElementID get_id() const = 0;
    virtual ReceiverType get_receiver_type() const = 0; //metoda 'idetyfikujaca' o której mowa we wskazowkach
};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;

    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t get_preferences() const {return probabilities;} //mozliwe ze to nie potrzebne, ale moze przydac
    const_iterator cbegin() const {return probabilities.cbegin();}
    const_iterator cend() const {return probabilities.cend();}
    iterator begin() {return probabilities.begin();}
    iterator end() {return probabilities.end();}
private:
    preferences_t probabilities;
};

class PackageSender {
public:
    ReceiverPreferences receiver_preferences_;
    void send_package();
    void push_package(Package&& package) {buffer.insert(buffer.cend(), package);}
protected:
    std::vector<Package> buffer; //daje glowe ze ten buffer sie bedzie pieprzyl xd

};



#endif //NET_SIM_NODES_HPP
