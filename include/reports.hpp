//
// Created by MICHAŁ on 11.12.2019.
//

#ifndef NET_SIM_REPORTS_HPP
#define NET_SIM_REPORTS_HPP

#include "types.hpp"
#include "factory.hpp"

void generate_structure_report(Factory& f, std::ostream& os);
void generate_simulation_turn_report(Factory& f, std::ostream& os, Time t);

#endif //NET_SIM_REPORTS_HPP
