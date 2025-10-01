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
    const size_t n = adjacency_matrix.size();
    if (n == 0) return result;
    if (from < 0 || from >=n) return result;
    if (to < 0 || to >=n) return result;

    const float infinity = std::numeric_limits<float>::infinity();
    const size_t undefined = std::numeric_limits<size_t>::max();

    std::vector<float> distance(n, infinity);
    std::vector<bool> visited(n, false);
    std::vector<size_t> queue(n);
    std::vector<size_t> previous(n, undefined);
    std::vector<float> heuristic(n, 0.0f);
    {
        float to_x = adjacency_matrix[to].pos_x;
        float to_y = adjacency_matrix[to].pos_y;
        for (auto i = 0; i < n; i++) {
            float dx = adjacency_matrix[i].pos_x - to_x;
            float dy = adjacency_matrix[i].pos_y - to_y;
            heuristic[i] = std::sqrt(dx*dx + dy*dy);
        }
    }

    queue.push_back(from);

    for (auto i = 0; i < n; i++) { queue[i] = i; }

    distance[from] = 0.0f; 
    
    while (num_visited < n) {
        auto bestDistance = infinity;
        auto bestIndex = undefined;

        for (auto i = 0; i < n; i++) {
            auto id = queue[i];
            if (!visited[id] && distance[id] + heuristic[id] < bestDistance) {
                bestDistance = distance[id] + heuristic[id];
                bestIndex = id;
            }
        }

        if (bestIndex == undefined) {break;} // no nodes

        visited[bestIndex] = true;
      

        if (bestIndex == to) { break; } // reached destination
        num_visited++;

        const auto& edges = adjacency_matrix[bestIndex];
        for (auto i = 0; i < n; i++) {
            if (visited[i]) { continue; }
            if (!edges[i].has_value()) { continue; }

            float weight = edges[i].value();
            float newDistance = distance[bestIndex] + weight;

            if (newDistance < distance[i]) {
                distance[i] = newDistance;
                previous[i] = bestIndex;
            }
        }
    }
    if (distance[to] == infinity) {
        std::cout << "Nodes visited: " << num_visited << std::endl;
        return result; 
    }

    auto current = to;
    while (current != undefined) {
        result.push_back(current);
        if (current == from) break;
        current = previous[current];
    }

    std::reverse(result.begin(), result.end());
    std::cout << "Nodes visited: " << num_visited << std::endl;
    return result;
}
