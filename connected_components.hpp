#pragma once

#include "graph.hpp"
#include <queue>

template <typename Vertex, typename Weight>
auto connected_components(
        const graph<Vertex, Weight>& grp
        )
{
    std::size_t conn_cmp_cnt = 0;

    std::map<Vertex, bool> visited;

    const auto& vertices = grp.verteces();
    for(const auto& vertex : vertices)
    {
        visited[vertex] = false;
    }

    for(const auto& vertex : vertices)
    {
        if(!visited[vertex])
        {
            ++conn_cmp_cnt;

            std::queue<Vertex> vertex_queue;
            vertex_queue.push(vertex); 

            while(!vertex_queue.empty())
            {
                const auto& current_vertex = vertex_queue.front(); vertex_queue.pop();

                visited[current_vertex] = true;

                const auto& neighbours = grp.neighbors(current_vertex);
                for(const auto& neighbour : neighbours)
                {
                    if(!visited[neighbour.first])
                    {
                        vertex_queue.push(neighbour.first);
                    }
                }
            }
        }
    }

    return conn_cmp_cnt;
}
