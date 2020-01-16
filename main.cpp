#include <iostream>
#include "factory.hpp"
#include "helpers.hpp"
#include "nodes.hpp"
#include "reports.hpp"
#include "simulation.hpp"
#include "types.hpp"
#include "storage_types.hpp"


int main() {
    auto recv = std::make_unique<Storehouse>(1);
    std::cout << "Hello, World!" << std::endl;

    auto tokens = parse_line("Ala ma kota.");
    for (const auto &token : tokens) {
        std::cout << token << std::endl;
    }

    return 0;
}
