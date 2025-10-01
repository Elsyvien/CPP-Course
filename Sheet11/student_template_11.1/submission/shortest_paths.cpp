#include "shortest_paths.h"
#include <algorithm>
#include <utility>
#include <iostream>
#include <cmath>

size_t ShortestPaths::getNodeIdByName(const std::string& name) const {
    // NOTE: if you like, you can make this more efficient by caching the mapping in a mutable hash map that gets reset when calling non-const functions
    const auto it = std::find_if(adjacency_matrix.begin(), adjacency_matrix.end(), [=](const Location& row) -> bool { return row.name == name; });
    if (it == adjacency_matrix.end())
        throw std::runtime_error("Location "+name+" not found");
    return static_cast<size_t>(std::distance(adjacency_matrix.begin(), it));
}

std::vector<size_t> ShortestPaths::compute_shortest_path(size_t from, size_t to) const
{
    /// your result path
    std::vector<size_t> result;
    /// increment this for every node that you pop from the queue
    size_t num_visited = 0;

    // TODO: your code here

    std::cout << "Nodes visited: " << num_visited << std::endl;

    return result;
}
