// 35: Michał Antos (302815), Szymon Brożyna (309040)

#ifndef NET_SIM_SIMULATION_HPP
#define NET_SIM_SIMULATION_HPP

#include "factory.hpp"
#include "types.hpp"

void simulate(Factory &factory, TimeOffset d, std::function<void(Factory &, Time)>);

class SpecificTurnsReportNotifier {
    SpecificTurnsReportNotifier(std::set<Time> turns_) : turns(turns_) {}
    bool should_generate_report(Time t);
private:
    std::set<Time> turns;
};

#endif //NET_SIM_SIMULATION_HPP
