// 35: Michał Antos (302815), Szymon Brożyna (309040)
#ifndef NET_SIM_TYPES_HPP
#define NET_SIM_TYPES_HPP

#include <cstdlib>
#include <iostream>
#include <random>
#include <ctime>
#include <functional>

using ElementID = int;
using Time = int;
using TimeOffset = int;

using ProbabilityGenerator = std::function<double()>;

#endif //NET_SIM_TYPES_HPP
