// 35: Michał Antos (302815), Szymon Brożyna (309040)

#ifndef NET_SIM_REPORTS_HPP
#define NET_SIM_REPORTS_HPP

#include "types.hpp"
#include "factory.hpp"

void generate_structure_report(const Factory &factory, std::ostream &os);

void generate_simulation_turn_report(const Factory &factory, std::ostream &os, Time t);

bool my_sort(std::pair<IPackageReceiver*,double> a, std::pair<IPackageReceiver*,double> b);

#endif //NET_SIM_REPORTS_HPP
