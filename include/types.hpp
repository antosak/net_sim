//
// Created by MICHAŁ on 11.12.2019.
//

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

double probability_generator_1();

using ProbabilityGenerator = std::function<double()>;


#endif //NET_SIM_TYPES_HPP
