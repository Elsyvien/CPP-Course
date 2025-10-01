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
    size_t num_nodes = size();
    if(num_nodes == 0) throw std::runtime_error("No Nodes");
    if(num_steps == 0) throw std::runtime_error("No Steps");
    std::random_device rand;
    std::mt19937 generate(rand()); 

    std::uniform_int_distribution<uint32_t> uniform_int(0, (uint32_t)(num_nodes - 1));
    size_t current_node = uniform_int(generate);
    for (size_t step = 0; step < num_steps; step++) {
        const std::vector<std::pair<uint32_t, float>>& out = get_edges_starting_at(current_node);
        if (out.empty()) {
            (*this)[current_node] = (*this)[current_node] + 1;
            continue;
        }
        float weight = 0.0f;
        for (auto i = 0; i < out.size(); i++) {
            weight = weight + out[i].second;
        }

        if (weight <= 0.0) {
            (*this)[current_node] = (*this)[current_node] + 1;
            continue;
        }
        std::uniform_real_distribution<float> uniform_float(0.0f, weight);
        float random_weight = uniform_float(generate);

        float cummulative_weight = 0.0f;
        auto next_node = current_node;
        for (auto i = 0; i < out.size(); i++) {
            cummulative_weight = cummulative_weight + out[i].second;
            if (random_weight <= cummulative_weight) {
                next_node = out[i].first;
                break;
            }
        }
        current_node = next_node;
        (*this)[current_node] = (*this)[current_node] + 1;
    }



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
    if (width * height != size()) {throw std::runtime_error("WRONG SIZE!");}

    std::ofstream file;
    file.open(filename, std::ios::binary);
    if (!file) {throw std::runtime_error("File opening not Possible!");}
    file << "P5\n" << width << " " << height << "\n" << 255 << "\n";

    std::vector<unsigned char> pixels = compute_normalized_histogram<unsigned char>(static_cast<unsigned char>(255));

    const char *pixel = reinterpret_cast<const char*>(pixels.data());
    std::streamsize size = static_cast<std::streamsize>(pixels.size() * sizeof(unsigned char));
    file.write(pixel, size);
    file.close(); 
}
