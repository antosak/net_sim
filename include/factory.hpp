// 35: Michał Antos (302815), Szymon Brożyna (309040)

#ifndef NET_SIM_FACTORY_HPP
#define NET_SIM_FACTORY_HPP

#include "nodes.hpp"
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

enum class NodeColor { UNVISITED, VISITED, VERIFIED };
enum class IOType {RAMP, WORKER, STOREHOUSE, LINK};

template <typename Node>
class NodeCollection{
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    void add(Node& node) {this -> container.push_back(std::move(node));}
    void remove_by_id(ElementID id_);

    NodeCollection<Node>::iterator find_by_id(ElementID id_) {return std::find_if(this -> container.begin(),
            this -> container.end(),[id_] (const Node& node) {return node.get_id() == id_;});}
    NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const {return std::find_if(this ->container.cbegin(),
            this ->container.cend(), [id_] (const Node& node) {return node.get_id() == id_;});}

    const_iterator cbegin() const { return this -> container.cbegin(); }
    const_iterator cend() const { return this -> container.cend(); }
    iterator begin() { return this -> container.begin(); }
    const_iterator begin() const { return this -> container.cbegin(); }
    iterator end() { return this -> container.end(); }
    const_iterator end() const { return this -> container.cend(); }

private:
    container_t container;
};

template<typename Node>
void NodeCollection<Node>::remove_by_id(ElementID id_) {
    NodeCollection<Node>::iterator node_to_erase = find_by_id(id_);
    if (node_to_erase != this -> container.end()) {
        this -> container.erase(node_to_erase);
    }
}

class Factory{
public:
    void add_ramp(Ramp&& ramp) {ramps.add(ramp);}
    void remove_ramp(ElementID id) {ramps.remove_by_id(id);}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramps.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return ramps.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramps.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramps.cend();}

    void add_worker(Worker&& worker) {workers.add(worker);}
    void remove_worker(ElementID id) {remove_receiver(workers, id);}
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return workers.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return workers.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin() const {return workers.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend() const {return workers.cend();}

    void add_storehouse(Storehouse&& storehouse) {storehouses.add(storehouse);}
    void remove_storehouse(ElementID id) {remove_receiver(storehouses, id);}
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {return storehouses.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return storehouses.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return storehouses.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return storehouses.cend();}


    void do_deliveries(Time t);
    void do_package_passing();
    void do_work(Time t);
    bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);
    bool is_consistent();


private:
    NodeCollection<Ramp> ramps;
    NodeCollection<Worker> workers;
    NodeCollection<Storehouse> storehouses;
    template <typename Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id);
};

template<typename Node>
void Factory::remove_receiver(NodeCollection<Node> &collection, ElementID id) {
    for (auto &worker : workers) {
        try {
            worker.receiver_preferences_.ReceiverPreferences::remove_receiver(&(*collection.find_by_id(id)));
        } catch (const std::logic_error &e) {
            std::cout<<e.what();
            continue;
        }
    }
    for (auto &ramp_ : ramps) {
        try {
            ramp_.receiver_preferences_.ReceiverPreferences::remove_receiver(&(*collection.find_by_id(id)));
        } catch (const std::logic_error &e) {
            std::cout<<e.what();
            continue;
        }
    }
    collection.remove_by_id(id);
}

Factory load_factory_structure(std::istream &is);
//    auto save_factory_structure(Factory &factory, std::ostream &os);

std::vector<std::string> parse_line(std::string line, char delimiter = ' ');
void add_element_from_string(std::vector<std::string> tokens, Factory &factory);

//    struct ParsedLineData {
//        IOType element_type;
//        //     parameters;
//    };
//};
#endif //NET_SIM_FACTORY_HPP