#include <iostream>
#include "factory.hpp"
#include "helpers.hpp"
#include "nodes.hpp"
#include "reports.hpp"
#include "simulation.hpp"
#include "types.hpp"
#include "storage_types.hpp"


int main() {
    Factory factory;
/* inicjalizacja fabryki */

// Testowanie z użyciem "wydmuszki" funkcji raportującej.
    simulate(factory, 3, [](Factory&, TimeOffset) {});

// Testowanie z użyciem konkretnego obiektu klasy raportującej.
    SpecificTurnsReportNotifier spec_notifier(std::set<Time>{1});
    simulate(factory, 3, [&spec_notifier](Factory& f, TimeOffset t_offset) {
        if (spec_notifier.should_generate_report(t_offset)) {
            generate_structure_report(f, std::cout);
        }
    });
}
