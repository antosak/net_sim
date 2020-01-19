// 35: Michał Antos (302815), Szymon Brożyna (309040)

#include "simulation.hpp"

void simulate(Factory &factory, TimeOffset d, std::function<void(Factory &, Time)> rf) {
    bool consistency = factory.is_consistent();
    if (!consistency){
        throw std::logic_error("Net is inconsistent");
    }else {
        for (TimeOffset turn = 1; turn <= d; turn++) {
            factory.do_deliveries(turn);
            factory.do_package_passing();
            factory.do_work(turn);
            rf(factory, turn);
        }
    }
}