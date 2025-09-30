#include "random_walk_graph.h"

#include <algorithm>
#include <fstream>
#include <ios>
#include <numeric>
#include <random>
#include <iostream>
#include <stdexcept>

void RandomWalkGraph::simulate_random_walk(uint32_t num_steps) {
    // TODO: 10.3 a)

    if constexpr (/* DISABLED - generates too much output if run thousands of times */ false) {
        // example for generating random integers (upper bound included)
        std::uniform_int_distribution<uint32_t> dice {1, 6};
        for (uint32_t i=0; i<10; ++i)
            std::cout << dice(prng) << " ";
        std::cout << std::endl;

        // example for generating random floating point values (upper bound excluded)
        std::uniform_real_distribution<float> uniform_float {0.0f, 1.0f};
        for (uint32_t i=0; i<10; ++i)
            std::cout << uniform_float(prng) << " ";
        std::cout << std::endl;
    }
}

void RandomWalkGraph::write_histogram_pgm(const std::string& filename, uint32_t width, uint32_t height) const {
    // TODO: 10.3 b)
}
