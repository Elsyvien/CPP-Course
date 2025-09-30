/*
Philipp Schmid
Max Staneker
*/

#include "adjacency_list_graph.h"

#include <stdexcept>
#include <algorithm>
#include <string>

void detail::AdjacencyListGraphBase::add_edge(uint32_t from, uint32_t to, float weight)
{
    size_t num_nodes = get_num_nodes();
    if (from >= num_nodes) {throw std::runtime_error("Error Start doesn't exist");}
    if (edges.size() <= from) {
        edges.resize(from + 1);
    }

    for (size_t i = 0; i < edges[from].size(); i++) {
        if (edges[from][i].first == to) throw std::runtime_error("Edge alread exists");
    }

    edges[from].push_back(std::make_pair(to, weight));

}

void detail::AdjacencyListGraphBase::remove_edge(uint32_t from, uint32_t to)
{
    size_t num_nodes = get_num_nodes();
    if (from >= num_nodes) {std::runtime_error("Error Start doesn't exist");}
    if (edges.size() <= from || edges[from].empty()) {throw std::runtime_error("Error edge doesnt exist");}

    for (size_t i = 0; i < edges[from].size();i++){
        if (edges[from][i].first == to) {
            edges[from].erase(edges[from].begin() + i);
            return;
        }
    }
    throw std::runtime_error("Edge doesnt exist");
}

std::optional<float> detail::AdjacencyListGraphBase::get_edge(uint32_t from, uint32_t to) const
{
    size_t num_nodes = get_num_nodes();
    if (from >= num_nodes || to >= num_nodes) {throw std::range_error("OUT OF RANGE!");} 
    if (edges.size() <= from) {return std::optional<float>();}

    const auto& edgesFrom = edges[from];
    for (auto& edge : edgesFrom) {
        if (edge.first == to) {
            return edge.second;
        }
    }
    return std::optional<float>();
}

const std::vector<std::pair<uint32_t, float>>& detail::AdjacencyListGraphBase::get_edges_starting_at(uint32_t node) const
{
    const std::vector<std::pair<uint32_t, float>> empty_edges;
    if (node >= get_num_nodes()) {return empty_edges;}
    if (node >= edges.size()) {return empty_edges;}

    return edges[node];
}
