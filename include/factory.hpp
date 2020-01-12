//// 35: Michał Antos (302815), Szymon Brożyna (309040)
//
//#ifndef NET_SIM_FACTORY_HPP
//#define NET_SIM_FACTORY_HPP
//
//#include "nodes.hpp"
//#include <algorithm>
//
//enum class NodeColor { UNVISITED, VISITED, VERIFIED };
//
//template <typename Node>
//class NodeCollection{
//public:
//    using container_t = typename std::list<Node>;
//    using iterator = typename container_t::iterator;
//    using const_iterator = typename container_t::const_iterator;
//
//    void add(Node& node) {container.push_back(std::move(node));} // na emplace_back krzyczy standardowo
//    void remove_by_id(ElementID id_);
//
//    NodeCollection<Node>::iterator find_by_id(ElementID id_) {return std::find_if(container.begin(),
//            container.end(),[id_] (const Node& node) {return node.get_id() == id_;});}
//
//    NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const {return std::find_if(container.cbegin(),
//            container.cend(), [id_] (const Node& node) {return node.get_id() == id_;});}
//
//    const_iterator cbegin() const { return container.cbegin(); }
//    const_iterator cend() const { return container.cend(); }
//    iterator begin() { return container.begin(); }
//    const_iterator begin() const { return container.cbegin(); }
//    iterator end() { return container.end(); }
//    const_iterator end() const { return container.cend(); }
//
//private:
//    container_t container;
//};
//
//template<typename Node>
//void NodeCollection<Node>::remove_by_id(ElementID id_) {
//    NodeCollection<Node>::iterator node_to_erase = find_by_id(id_);
//    if (node_to_erase != container.end()) {
//        container.erase(node_to_erase);
//    }
//}
//
//class Factory{
//public:
//    void add_ramp(Ramp&& ramp) {ramps.add(ramp);}
//    void remove_ramp(ElementID id) {ramps.remove_by_id(id);}
//    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id) {return ramps.find_by_id(id);}
//    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const {return ramps.find_by_id(id);}
//    NodeCollection<Ramp>::const_iterator ramp_cbegin() const {return ramps.cbegin();}
//    NodeCollection<Ramp>::const_iterator ramp_cend() const {return ramps.cend();}
//
//    void add_worker(Worker&& worker) {workers.add(worker);}
//    void remove_worker(ElementID id) {workers.remove_by_id(id);}
//    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id) {return workers.find_by_id(id);}
//    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const {return workers.find_by_id(id);}
//    NodeCollection<Worker>::const_iterator worker_cbegin() const {return workers.cbegin();}
//    NodeCollection<Worker>::const_iterator worker_cend() const {return workers.cend();}
//
//    void add_storehouse(Storehouse&& storehouse) {storehouses.add(storehouse);}
//    void remove_storehouse(ElementID id) {storehouses.remove_by_id(id);}
//    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id) {return storehouses.find_by_id(id);}
//    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const {return storehouses.find_by_id(id);}
//    NodeCollection<Storehouse>::const_iterator storehouse_cbegin() const {return storehouses.cbegin();}
//    NodeCollection<Storehouse>::const_iterator storehouse_cend() const {return storehouses.cend();}
//
//    void do_deliveries(Time t);
//    void do_package_passing();
//    void do_work(Time t);
//
//
//    bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors);
//    bool is_consistent();
//
//
//private:
//    NodeCollection<Ramp> ramps;
//    NodeCollection<Worker> workers;
//    NodeCollection<Storehouse> storehouses;
//    template <typename Node>
//    void remove_receiver(NodeCollection<Node>& collection, ElementID id);
//};
//
//template<typename Node>
//void Factory::remove_receiver(NodeCollection<Node> &collection, ElementID id) {
//    for (auto &worker_ : workers) {
//        try {
//            worker_.receiver_preferences_.remove_receiver(NodeCollection<Node>::find_by_id(id));
//        } catch (const std::logic_error &e) {
//            e.what();
//            continue;
//        }
//    }
//    for (auto &ramp_ : ramps) {
//        try {
//            ramp_.receiver_preferences_.remove_receiver(NodeCollection<Node>::find_by_id(id));
//        } catch (const std::logic_error &e) {
//            e.what();
//            continue;
//        }
//    }
//    collection.remove_by_id(id);
//}
//
//
//#endif //NET_SIM_FACTORY_HPP