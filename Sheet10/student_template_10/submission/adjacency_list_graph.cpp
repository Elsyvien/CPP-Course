#include "adjacency_list_graph.h"

#include <stdexcept>
#include <algorithm>
#include <string>

void detail::AdjacencyListGraphBase::add_edge(uint32_t from, uint32_t to, float weight)
{
    // TODO: task 10.1 a)

}

void detail::AdjacencyListGraphBase::remove_edge(uint32_t from, uint32_t to)
{
    // TODO: task 10.1 b)

}

std::optional<float> detail::AdjacencyListGraphBase::get_edge(uint32_t from, uint32_t to) const
{
    // TODO: task 10.1 c)

}

const std::vector<std::pair<uint32_t, float>>& detail::AdjacencyListGraphBase::get_edges_starting_at(uint32_t node) const
{
    // TODO: task 10.1 d)

}
