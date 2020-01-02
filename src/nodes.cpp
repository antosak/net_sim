//
// Created by MICHAŁ on 11.12.2019.
//
#include "nodes.hpp"
#include <exception>

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    probabilities[r] = 0;
    double new_prob = 1 / probabilities.size();
    for (auto prob : probabilities) {
        prob.second = new_prob; // utrzymywanie sumy prawdopodobieństw równa 1
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    auto prob_to_remove = probabilities.find(r);
    bool prob_exists = prob_to_remove != probabilities.end();
    if (prob_exists) {
        auto prob_value = prob_to_remove->second;
        probabilities.erase(prob_to_remove);
        for (auto prob : probabilities) {
            prob.second = prob.second / (1 - prob_value);
        }
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    double n = probability_generator_1();
    for (const auto &prob : probabilities) {
        if (prob.second >= n)
            return prob.first;
    }
    throw std::logic_error("Cannot draw a receiver");
}

void PackageSender::send_package() {
}

void Ramp::deliver_goods(Time t) {
    if (t - 1 % di == 0) {
        buffer.emplace_back(Package());
    }
}

void Worker::do_work(Time t) {
    if ()
}
