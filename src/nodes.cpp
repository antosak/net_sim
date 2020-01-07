// <nr grupy>: Michał Antos (302815), Szymon Brożyna (309040)
#include "nodes.hpp"

void ReceiverPreferences::add_receiver(IPackageReceiver *r) {
    probabilities[r] = 0;
    double new_prob = (double) 1 / probabilities.size();
    for (auto &prob : probabilities) {
        prob.second = new_prob;
    } // keeping the probabilities in check
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r) {
    auto prob_to_remove = probabilities.find(r);
    bool prob_exists = prob_to_remove != probabilities.end();
    if (prob_exists) {
        auto prob_value = prob_to_remove->second;
        probabilities.erase(prob_to_remove);
        for (auto &prob : probabilities) {
            prob.second = (double) prob.second / (1 - prob_value);
        } // keeping the probabilities in check
    } else {
        throw std::logic_error("Desired receiver does not exist.");
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver() {
    double n = default_probability_generator();
    double distribution = 0;
    for (const auto &prob : probabilities) {
        distribution += prob.second;
        if (distribution >= n)
            return prob.first;
    }
    throw std::logic_error("Cannot choose a receiver");
}

void PackageSender::send_package() {
    if (buffer) {
        auto chosen_one = receiver_preferences_.choose_receiver();
        chosen_one->receive_package(std::move(buffer.value()));
        buffer.reset();
    }
}

std::optional<Package> &PackageSender::get_sending_buffer() {
    return buffer;
}

void Ramp::deliver_goods(Time t) {
    if (buffer != std::nullopt){
        throw std::logic_error("There is a different product on the ramp");
    }
    if ((t % di) == 0) {
        buffer = std::optional<Package>(Package());
    }
}

void Worker::do_work(Time t) {
    if (process_object) {
        bool is_product_done = (get_processing_duration() == (t - get_package_processing_start_time() + 1));
        if (is_product_done) {
            buffer = std::move(process_object);
            process_object.reset();
        }
    } // case where worker works on a package
    else {
        process_object = std::optional<Package>(q->pop());
        pst = t;
    } // case where package has been received and nothing is being worked on
}

