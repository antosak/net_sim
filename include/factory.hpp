// 35: Michał Antos (302815), Szymon Brożyna (309040)

#ifndef NET_SIM_FACTORY_HPP
#define NET_SIM_FACTORY_HPP

#include "nodes.hpp"
#include <algorithm>

class Factory{
public:
    void add_ramp(Ramp&& ramp) {ramps.emplace_back(std::move(ramp));}
    void remove_ramp(ElementID id);
    NodeCollection<Node>::iterator find_ramp_by_id(ElementID id){return std::find_if(ramps.begin(), ramps.end(), [id] (Ramp&& r){return (r.get_id() == id);});}


    void add_worker(Worker&& worker) {workers.push_back(std::move(worker));}
    void remove_worker(ElementID id);

    void add_storehouse(Storehouse&& storehouse) {storehouses.emplace_back(std::move(storehouse));}
    void remove_storehouse(ElementID id);

    bool is_consistent();


    void add_worker(Storehouse&& storehouse) {storehouses.emplace_back(std::move(storehouse));}



    bool is_consistent(){return true;}
    void do_deliveries();
    void do_package_passing();
    void do_work();
private:
    std::list<Ramp> ramps;
    std::list<Worker> workers;
    std::list<Storehouse> storehouses;
};

template <typename Node>
class NodeCollection{
    //void add(Node& node){std::move(node)}
    //void remove_by_id(ElementID id_){}
    //NodeCollection<Node>::iterator find_by_id(ElementID id_){std::find_if()}
    //NodeCollection<Node>::const_iterator const find_by_id(ElementID id_){}

    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
};

#endif //NET_SIM_FACTORY_HPP