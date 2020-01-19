// 35: Michał Antos (302815), Szymon Brożyna (309040)

#ifndef NET_SIM_SIMULATION_HPP
#define NET_SIM_SIMULATION_HPP

#include "factory.hpp"
#include "types.hpp"

void simulate(Factory &factory, TimeOffset d, std::function<void(Factory &, Time)>);

class IntervalReportNotifier{
public:
    IntervalReportNotifier(TimeOffset to_) : to(to_) {}
    bool should_generate_report(Time t) {return t - 1 % to == 0;};
private:
    TimeOffset to;
};

#endif //NET_SIM_SIMULATION_HPP
