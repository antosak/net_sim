//
// Created by MICHAŁ on 11.12.2019.
//
#include <random>
#include "helpers.hpp"

double probability_generator_1() {
    std::random_device rd;
    std::mt19937 rng(rd());
    return std::generate_canonical<double, 10>(rng);
}
