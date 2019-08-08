#pragma once

#include <utility>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <algorithm>
#include <iostream>

template <typename Vertex = int, typename Weight = double>
class graph
{
    public:
        typedef Vertex vertex_type;
        typedef Weight weight_type;
        typedef std::pair<Vertex, Weight> neighbor_type;
        typedef std::vector<neighbor_type> neighbor_list_type;

    public:
        void add_edge(Vertex const source, Vertex const target,
                Weight const weight, bool const bidir = true)
        {
            adj_list[source].push_back(std::make_pair(target, weight));
            adj_list[target].push_back(std::make_pair(source, weight));
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
