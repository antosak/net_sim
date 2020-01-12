// 35: Michał Antos (302815), Szymon Brożyna (309040)

#include "factory.hpp"

bool Factory::is_consistent() {
    std::map<const PackageSender*, NodeColor> node_colors;
    for (auto &worker_ : workers) {
        node_colors[&worker_] = NodeColor::UNVISITED;
    }
    for (auto &ramp_: ramps) {
        node_colors[&ramp_] = NodeColor::UNVISITED;
    }




    return false;
}

void Factory::do_work(Time t) {
    for (auto &worker_ : workers) {
        worker_.do_work(t);
    }
}

void Factory::do_package_passing(){
    for (auto &worker_ : workers) {
        if (worker_.buffer) {
            worker_.send_package();
        }
    }
    for (auto &ramp_: ramps) {
        if (ramp_.buffer) {
            ramp_.send_package();
        }
    }
}

void Factory::do_deliveries(Time t) {
    for (auto &ramp_ : ramps) {
        ramp_.deliver_goods(t);
    }
}

template<typename Node>
void Factory::remove_receiver(NodeCollection<Node> &collection, ElementID id) {
    collection.remove_by_id(id);
}

bool Factory::has_reachable_storehouse(const PackageSender *sender,
                                       std::map<const PackageSender *, NodeColor> &node_colors) {

    if(node_colors[sender] == NodeColor::VERIFIED)
        return true;
    else
        node_colors[sender] = NodeColor::VISITED;

    if (sender->receiver_preferences_.get_preferences().empty()){
        throw std::logic_error("Sieć nie jest spójna.");
    }

//    bool does_sender_have_receiver = false;
//
//    for(auto sender_ : node_colors)

    return false;
}


