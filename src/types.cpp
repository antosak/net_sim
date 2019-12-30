//
// Created by MICHAŁ on 11.12.2019.
//
#include "types.hpp"
std::random_device rd;
std::mt19937 rng(rd());

double probability_generator_1() {
    return std::generate_canonical<double, 10>(rng);
}