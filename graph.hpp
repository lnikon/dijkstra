#pragma once

#include <utility>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <algorithm>
#include <iostream>

#include "union_find.hpp"

template <typename Vertex = int, typename Weight = double>
class graph
{
    public:
        using vertex_type = Vertex;
        using weight_type = Weight;
        using neighbor_type = std::pair<Vertex, Weight>;
        using neighbor_list_type = std::vector<neighbor_type>;
        using degree_type = std::size_t;

    public:
        void add_edge(Vertex const source, Vertex const target,
                Weight const weight, bool const bidir = true)
        {
            adj_list[source].push_back(std::make_pair(target, weight));
            adj_list[target].push_back(std::make_pair(source, weight));

            degrees[source]++;
            degrees[target]++;
        }

        std::size_t vertex_count() const { return adj_list.size(); }

        std::vector<Vertex> verteces() const
        {
            std::vector<Vertex> keys;
            for(auto const & kvp : adj_list)
            {
                keys.push_back(kvp.first);
            }

            return keys;
        }

        std::vector<std::pair<vertex_type, degree_type>> degree_sequence() const
        {
            std::vector<std::pair<vertex_type, degree_type>> degree_seq;
            for(const auto [vertex, degree] : degrees)
            {
                degree_seq.push_back({vertex, degree});
            }

            std::sort(std::begin(degree_seq), std::end(degree_seq), [](const auto& lhs_vert_deg, const auto& rhs_vert_deg) {
                    return lhs_vert_deg.first < rhs_vert_deg.second; });

            return degree_seq;
        }

        graph<Vertex, Weight> spanning_tree() const
        {
            using sorted_edge_type = std::pair<Weight, std::pair<Vertex, Vertex>>;
            struct cmp_sorted_edge_type
            {
                bool operator()(const sorted_edge_type& lhs, const sorted_edge_type& rhs)
                {
                    return lhs.first < rhs.first;
                }
            };

            const auto& vertices = verteces();
            union_find<Vertex> unfnd(vertices);

            std::set<sorted_edge_type, cmp_sorted_edge_type> sorted_edges;
            
            for(const auto& vertex : adj_list)
            {
                for(const auto& nigga : vertex.second)
                {
                    sorted_edges.emplace(std::make_pair(nigga.second, std::make_pair(vertex.first, nigga.first)));
                }
            }

            return graph<Vertex, Weight>{};
        }

        neighbor_list_type const & neighbors(Vertex const & v) const
        {
            auto pos = adj_list.find(v);
            if(pos == adj_list.end())
            {
                throw std::runtime_error("vertex not found");
            }

            return pos->second;
        }

        constexpr static Weight Infinity = 
            std::numeric_limits<Weight>::infinity();

    private:
        std::map<vertex_type, neighbor_list_type> adj_list;
        std::map<vertex_type, degree_type> degrees;
};

//template <typename Vertex, typename Weight>
//void shortest_path(
//        graph<Vertex, Weight> const & g,
//        Vertex const source,
//        std::map<Vertex, Weight>& min_distance,
//        std::map<Vertex, Vertex>& previous
//        )
//{
//    auto const verteces = g.verteces();
//
//    min_distance.clear();
//    for(auto const & v : verteces)
//    {
//        min_distance[v] = graph<Vertex, Weight>::Infinity;
//    }
//    min_distance[source] = 0;
//
//    previous.clear();
//
//    std::set<std::pair<Weight, Vertex>> vertex_queue;
//    vertex_queue.insert(std::make_pair(min_distance[source], source));
//
//    while(!vertex_queue.empty())
//    {
//        auto dist = vertex_queue.begin()->first;
//        auto u = vertex_queue.begin()->second;
//
//        vertex_queue.erase(std::begin(vertex_queue));
//
//        auto const & neighbors = g.neighbors(u);
//        for(const auto & neighbor : neighbors)
//        {
//            auto v = neighbor.first;
//            auto w = neighbor.second;
//            auto dist_via_u = dist + w;
//            if(dist_via_u < min_distance[v])
//            {
//                vertex_queue.erase(std::make_pair(min_distance[v], v));
//                min_distance[v] = dist_via_u;
//                previous[v] = u;
//                vertex_queue.insert(std::make_pair(min_distance[v], v));
//            }
//        }
//    }
//}
//
//template <typename Vertex>
//void build_path(
//        std::map<Vertex, Vertex> const & prev,
//        Vertex const v,
//        std::vector<Vertex> & result
//        )
//{
//    result.push_back(v);
//
//    auto pos = prev.find(v);
//    if(pos == std::end(prev))
//    {
//        return ;
//    }
//
//    build_path(prev, pos->second, result);
//}
//
//template <typename Vertex>
//std::vector<Vertex> build_path(
//        std::map<Vertex, Vertex> const & prev,
//        Vertex const v
//        )
//{
//    std::vector<Vertex> result;
//    build_path(prev, v, result);
//    std::reverse(std::begin(result), std::end(result));
//
//    return result;
//}
//
//template <typename Vertex>
//void print_path(std::vector<Vertex> const & path)
//{
//    for(std::size_t i = 0; i < path.size(); ++i)
//    {
//        std::cout << path[i];
//        if(i < path.size() - 1) std::cout << " -> ";
//    }
//    std::cout << std::endl;
//}
