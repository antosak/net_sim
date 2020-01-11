// 35: Michał Antos (302815), Szymon Brożyna (309040)

#ifndef NET_SIM_FACTORY_HPP
#define NET_SIM_FACTORY_HPP

#include "nodes.hpp"

class Factory{
public:
    void add_ramp(Ramp&& ramp) {ramps.emplace_back(std::move(ramp));}

    void add_worker(Worker&& worker) {workers.emplace_back(std::move(worker));}

private:
    std::list<Ramp> ramps;
    std::list<Worker> workers;
    std::list<Storehouse> storehouses;
};
#endif //NET_SIM_FACTORY_HPP
