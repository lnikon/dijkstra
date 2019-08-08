#include "graph.hpp"

#include <queue>

template <typename Vertex, typename Weight>
void shortest_path(
        const graph<Vertex, Weight>& grp,
        const Vertex& source,
        const std::map<Vertex, Weight>& min_dist 
        )
{
    min_dist.clear();

    const auto& vertices = grp.vertices();
    for(const auto& vertex : vertices)
    {
        min_dist[vertex] = graph<Vertex, Weight>::Infinity;
    }

    min_dist[source] = 0;

    std::set<std::pair<Weight, Vertex>> q;
    q.push(std::make_pair(min_dist[source], source));

    while(!q.empty())
    {
        auto dist = q.begin->first;
        auto w = q.begin()->second;

        q.erase(std::begin(q));
            
        const auto& neighbours = grp.neighbours(w);
        for(const auto& neighbour : neighbours)
        {
            auto d = neighbour.first;
            auto v = neighbour.second;
            auto dist_via_w = dist + d;
            if(dist_via_w < min_dist[v])
            {
                q.erase(std::make_pair(min_dist[v], v));
                min_dist[v] = dist_via_w;
                q.insert(std::make_pair(min_dist[v], v));
            }
        }
    }
}

template <typename Vertex>
void build_path(
        std::map<Vertex, Vertex> const & prev,
        Vertex const v,
        std::vector<Vertex> & result
        )
{
    result.push_back(v);

    auto pos = prev.find(v);
    if(pos == std::end(prev))
    {
        return ;
    }

    build_path(prev, pos->second, result);
}

template <typename Vertex>
std::vector<Vertex> build_path(
        std::map<Vertex, Vertex> const & prev,
        Vertex const v
        )
{
    std::vector<Vertex> result;
    build_path(prev, v, result);
    std::reverse(std::begin(result), std::end(result));

    return result;
}

template <typename Vertex>
void print_path(std::vector<Vertex> const & path)
{
    for(std::size_t i = 0; i < path.size(); ++i)
    {
        std::cout << path[i];
        if(i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
}
