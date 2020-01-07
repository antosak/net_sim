// <nr grupy>: Michał Antos (302815), Szymon Brożyna (309040)
#ifndef NET_SIM_NODES_HPP
#define NET_SIM_NODES_HPP

#include "types.hpp"
#include "package.hpp"
#include "helpers.hpp"
#include "storage_types.hpp"
#include <map>
#include <vector>
#include <memory>
#include <optional>
#include <exception>

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

    ReceiverPreferences(ProbabilityGenerator generator = default_probability_generator) : num_generator(generator){};
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t get_preferences() const {return probabilities;}
    const_iterator cbegin() const {return probabilities.cbegin();}
    const_iterator cend() const {return probabilities.cend();}
    const_iterator begin() {return probabilities.begin();}
    const_iterator end() {return probabilities.end();}
private:
    preferences_t probabilities;
    ProbabilityGenerator num_generator;
};

class PackageSender {
public:
    void send_package();
    std::optional<Package>& get_sending_buffer();
    ReceiverPreferences receiver_preferences_;
    std::optional<Package> buffer;
protected:
private:
};

class Ramp : public PackageSender {
public:
    Ramp(ElementID id_, TimeOffset di_) : id(id_), di(di_) {};
    ElementID get_id() const {return id;}
    TimeOffset get_delivery_interval() const {return di;}
    void deliver_goods(Time t); //function puts packages into the buffer
private:
    ElementID id;
    TimeOffset di;
};

class Worker : public IPackageReceiver, public PackageSender {
public:
    void receive_package(Package&& p) override {q->push(std::move(p));}
    Worker(ElementID id_, TimeOffset pd_, std::unique_ptr<IPackageQueue> q_) : id(id_), pd(pd_), q(std::move(q_)){}
    ~Worker(){};
    void do_work(Time t);
    TimeOffset get_processing_duration(){return pd;}
    Time get_package_processing_start_time(){return pst;}
    ReceiverType get_receiver_type() const override {return ReceiverType::WORKER;}
    ElementID get_id()const override {return id;}
    auto size() {return q->size();} //only for tests
private:
    ElementID id;
    TimeOffset pd;
    std::unique_ptr<IPackageQueue> q;
    std::optional<Package> process_object = std::nullopt;
    Time pst = 0;
};

class Storehouse : public IPackageReceiver{
public:
    Storehouse(ElementID id_, std::unique_ptr<IPackageStockpile> d_) : id(id_), d(std::move(d_)) {}
    ElementID get_id() const override {return id;}
    ReceiverType get_receiver_type() const override {return ReceiverType::STOREHOUSE;}
    void receive_package(Package&& p) override {d->push(std::move(p));}
    auto size() {return d->size();} //only for tests
private:
    ElementID id;
    std::unique_ptr<IPackageStockpile> d;

};

#endif //NET_SIM_NODES_HPP
