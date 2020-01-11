// 35: Michał Antos (302815), Szymon Brożyna (309040)

#ifndef NET_SIM_FACTORY_HPP
#define NET_SIM_FACTORY_HPP

#include "nodes.hpp"
#include <algorithm>

class Factory{
public:
    void add_ramp(Ramp&& ramp) {ramps.emplace_back(std::move(ramp));}
    void remove_ramp(ElementID id);
    NodeCollection<Node>::iterator find_ramp_by_id(ElementID id) {return std::find_if(ramps.begin(), ramps.end(),
            [id] (Ramp&& r){return (r.get_id() == id);});}


    void add_worker(Worker&& worker) {workers.push_back(std::move(worker));}
    void remove_worker(ElementID id);

    void add_storehouse(Storehouse&& storehouse) {storehouses.emplace_back(std::move(storehouse));}
    void remove_storehouse(ElementID id);

    bool is_consistent();


private:
    std::list<Ramp> ramps;
    std::list<Worker> workers;
    std::list<Storehouse> storehouses;
};
#endif //NET_SIM_FACTORY_HPP
