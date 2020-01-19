// 35: Michał Antos (302815), Szymon Brożyna (309040)
// testowa linijka, nowy nieuszkodzony projekt
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
    using const_iterator = IPackageStockpile::const_iterator;

    virtual ~IPackageReceiver() {};

    virtual void receive_package(Package &&p) = 0;

    virtual ElementID get_id() const = 0;

    virtual ReceiverType get_receiver_type() const = 0;

    virtual const_iterator cbegin() const = 0;

    virtual const_iterator cend() const = 0;

    virtual const_iterator begin() const = 0;

    virtual const_iterator end() const = 0;
};

class ReceiverPreferences {
public:
    using preferences_t = std::map<IPackageReceiver *, double>;
    using const_iterator = preferences_t::const_iterator;

    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : num_generator(pg) {};

    void add_receiver(IPackageReceiver *r);

    void remove_receiver(IPackageReceiver *r);

    IPackageReceiver *choose_receiver();

    const preferences_t &get_preferences() const { return probabilities; }

    const_iterator cbegin() const { return probabilities.cbegin(); }

    const_iterator cend() const { return probabilities.cend(); }

    const_iterator begin() { return probabilities.begin(); }

    const_iterator end() { return probabilities.end(); }

private:
    preferences_t probabilities;
    ProbabilityGenerator num_generator;
};

class PackageSender {
public:
    PackageSender(PackageSender &&) = default;

    explicit PackageSender() : receiver_preferences_(), buffer() {};

    void send_package();

    const std::optional<Package> &get_sending_buffer() const { return buffer; };
    ReceiverPreferences receiver_preferences_;
    std::optional<Package> buffer = std::nullopt;

protected:
    void push_package(Package &&p) { buffer = std::optional<Package>(std::move(p)); }

};

class Ramp : public PackageSender {
public:
    Ramp(ElementID id_, TimeOffset di_) : id(id_), di(di_) {};

    ElementID get_id() const { return id; }

    TimeOffset get_delivery_interval() const { return di; }

    void deliver_goods(Time t); //function puts packages into the buffer
private:
    ElementID id;
    TimeOffset di;
};

class Worker : public IPackageReceiver, public PackageSender {
public:
    Worker(Worker &&worker) : id(worker.id), pd(worker.pd), q(std::move(worker.q)) {
        process_object = std::move(worker.process_object);
        pst = worker.pst;
    }

    void receive_package(Package &&p) override { q->push(std::move(p)); }

    Worker(ElementID id_, TimeOffset pd_, std::unique_ptr<IPackageQueue> q_) : id(id_), pd(pd_), q(std::move(q_)) {}

    ~Worker() {};

    void do_work(Time t);

    TimeOffset get_processing_duration() const { return pd; }

    Time get_package_processing_time(Time t) const { return t - pst + 1; }

    Time get_package_processing_start_time() const { return pst; }

    ReceiverType get_receiver_type() const override { return ReceiverType::WORKER; }

    ElementID get_id() const override { return id; }

    IPackageQueue *get_queue() const { return q.get(); }

    auto size() { return q->size(); }

    const_iterator cbegin() const override { return q->cbegin(); }

    const_iterator cend() const override { return q->cend(); }

    const_iterator begin() const override { return q->begin(); }

    const_iterator end() const override { return q->end(); }

    const std::optional<Package> &get_processing_buffer() const { return process_object; }

private:
    ElementID id;
    TimeOffset pd;
    std::unique_ptr<IPackageQueue> q;
    std::optional<Package> process_object = std::nullopt;
    Time pst = 0;
};

class Storehouse : public IPackageReceiver {
public:
    Storehouse(ElementID id_, std::unique_ptr<IPackageStockpile> d_ = std::make_unique<PackageQueue>()) : id(id_),
                                                                                                          d(std::move(
                                                                                                                  d_)) {}

    ElementID get_id() const override { return id; }

    ReceiverType get_receiver_type() const override { return ReceiverType::STOREHOUSE; }

    void receive_package(Package &&p) override { d->push(std::move(p)); }

    auto size() { return d->size(); } //only for tests
    const_iterator cbegin() const override { return d->cbegin(); }

    const_iterator cend() const override { return d->cend(); }

    const_iterator begin() const override { return d->begin(); }

    const_iterator end() const override { return d->end(); }

    IPackageStockpile *get_queue() const { return d.get(); }

private:
    ElementID id;
    std::unique_ptr<IPackageStockpile> d;

};

std::string str(ReceiverType receiverType);

std::string str(PackageQueueType packageQueueType);

std::string str_rep(ReceiverType receiverType);

#endif //NET_SIM_NODES_HPP
