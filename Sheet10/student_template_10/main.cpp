#include "submission/adjacency_list_graph.h"
#include "submission/random_walk_graph.h"

#include <cstdint>
#include <cstdlib>

#include <fstream>
#include <ios>
#include <iostream>
#include <array>
#include <cassert>
#include <cstring>

int main() {

    // how to work with existing code bases:
    // https://dilbert.com/strip/2018-11-13

    // TODO: task 10.2 b)
    try {
        RandomWalkGraph graph = RandomWalkGraph::deserialize("secret.graph");
        std::cout << "Imported nodes";
    } catch (const std::exception& e) {
        std::cerr << "Error while importing graph: " << e.what() << std::endl;
    }
    return 0;
    // TODO: task 10.3 a)

    // TODO: task 10.3 c)

    return EXIT_SUCCESS;
}
