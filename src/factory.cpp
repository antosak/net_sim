// 35: Michał Antos (302815), Szymon Brożyna (309040)

#include <sstream>
#include "factory.hpp"

bool Factory::is_consistent() {
    std::map<const PackageSender *, NodeColor> node_colors;
    for (auto &worker_ : workers) {
        node_colors[&worker_] = NodeColor::UNVISITED;
    }
    for (auto &ramp_: ramps) {
        node_colors[&ramp_] = NodeColor::UNVISITED;
    }
    for (auto &ramp_: ramps) {
        try {
            has_reachable_storehouse(&ramp_, node_colors);
        } catch (const std::logic_error &e) {
            std::cout << e.what();

            return false;
        }
    }

    return true;
}

void Factory::do_work(Time t) {
    for (auto &worker_ : workers) {
        worker_.do_work(t);
    }
}

void Factory::do_package_passing() {
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

bool Factory::has_reachable_storehouse(const PackageSender *sender,
                                       std::map<const PackageSender *, NodeColor> &node_colors) {

    if (node_colors[sender] == NodeColor::VERIFIED)
        return true;
    else
        node_colors[sender] = NodeColor::VISITED;

    if (sender->receiver_preferences_.get_preferences().empty()) {
        throw std::logic_error("No desired receiver.");
    }

    bool does_sender_have_receiver = false;
    for (auto receiver_ : sender->receiver_preferences_.get_preferences()) {
        if (receiver_.first->get_receiver_type() == ReceiverType::STOREHOUSE) {
            does_sender_have_receiver = true;
        } else {
            IPackageReceiver *receiver_ptr = receiver_.first;
            auto worker_ptr = dynamic_cast<Worker *>(receiver_ptr);
            auto sendrecv_ptr = dynamic_cast<PackageSender *>(worker_ptr);
            if (sendrecv_ptr == sender) {
                continue;
            } else if (node_colors[sendrecv_ptr] == NodeColor::UNVISITED &&
                       has_reachable_storehouse(sendrecv_ptr, node_colors)) {
                does_sender_have_receiver = true;
            }
        }
    }
    if (does_sender_have_receiver) {
        node_colors[sender] = NodeColor::VERIFIED;
        return true;
    } else { throw std::logic_error("YOU SHALL NOT PASS! There is no way to the storehouse"); }
}


//auto IO::save_factory_structure(Factory &factory, std::ostream &os) {
//return os -> zapisz linie
//}

Factory load_factory_structure(std::istream &is) {
    Factory factory;
    std::string line;
    std::vector<std::string> tokens;
    std::map<std::string, std::string> map;

    while (std::getline(is, line)) {
        if (line.empty() || line.at(0) == ';') {
            continue;
        } else {
            tokens = parse_line(line);
            add_element_from_string(tokens,factory);
        }
    }
return factory;
}

std::vector<std::string> parse_line(std::string line, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;

    std::istringstream token_stream(line);

    while (std::getline(token_stream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void add_element_from_string(std::vector<std::string> tokens, Factory &factory) {
    if (tokens[0] == "LOADING_RAMP") {
        int id = std::stoi(parse_line(tokens[1], '=')[1]);
        int di = std::stoi(parse_line(tokens[2], '=')[1]);
        factory.add_ramp(Ramp(id, di));
    }

    if (tokens[0] == "WORKER") {
        int id = std::stoi(parse_line(tokens[1], '=')[1]);
        int pd = std::stoi(parse_line(tokens[2], '=')[1]);
        std::string qt_str = parse_line(tokens[3], '=')[1];
        PackageQueueType qt;
        if (qt_str == "FIFO")
            qt = PackageQueueType::FIFO;
        else if (qt_str == "LIFO")
            qt = PackageQueueType::LIFO;

        factory.add_worker(Worker(id, pd, std::make_unique<PackageQueue>(qt)));

    }

    if (tokens[0] == "STOREHOUSE") {
        int id = std::stoi(parse_line(tokens[1], '=')[1]);
        factory.add_storehouse(Storehouse(id));
    }

    if (tokens[0] == "LINK") {
        std::string src = parse_line(parse_line(tokens[1], '=')[1], '-')[0];
        std::string dest = parse_line(parse_line(tokens[2], '=')[1], '-')[0];
        int src_id = std::stoi(parse_line(parse_line(tokens[1], '=')[1], '-')[1]);
        int dest_id = std::stoi(parse_line(parse_line(tokens[2], '=')[1], '-')[1]);

        if (src == "ramp") {
            if (dest == "worker") {
                factory.find_ramp_by_id(src_id)->receiver_preferences_.add_receiver(
                        &(*factory.find_worker_by_id(dest_id)));
            } else if (dest == "store") {
                factory.find_ramp_by_id(src_id)->receiver_preferences_.add_receiver(
                        &(*factory.find_storehouse_by_id(dest_id)));
            }
        } else if (src == "worker") {
            if (dest == "worker") {
                factory.find_worker_by_id(src_id)->receiver_preferences_.add_receiver(
                        &(*factory.find_worker_by_id(dest_id)));
            } else if (dest == "store") {
                factory.find_worker_by_id(src_id)->receiver_preferences_.add_receiver(
                        &(*factory.find_storehouse_by_id(dest_id)));
            }

        }
    }
}
