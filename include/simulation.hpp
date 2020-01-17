// 35: Michał Antos (302815), Szymon Brożyna (309040)

#ifndef NET_SIM_SIMULATION_HPP
#define NET_SIM_SIMULATION_HPP

#include "factory.hpp"
#include "types.hpp"

void simulate(Factory& factory, TimeOffset d, std::function<void(Factory&, Time)>);

#endif //NET_SIM_SIMULATION_HPP
