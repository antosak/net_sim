// 35: Michał Antos (302815), Szymon Brożyna (309040)

#include "factory.hpp"

//bool Factory::is_consistent() {
//    return false;
//}
//
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


