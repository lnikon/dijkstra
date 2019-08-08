#pragma once

#include <unordered_map>
#include <vector>

template <class Node>
class union_find
{
    public:
        union_find(const std::vector<Node>& nodes)
        {
            for(const auto& node : nodes)
            {
                reps[node] = node;
            }
        }

        auto find_set(const Node& node) const
        {
            if(node == reps[node])
            {
                return node;
            }
            else
            {
                return find_set(reps[node]);
            }
        }

        void union_set(const Node& from, const Node& to)
        {
            reps[from] = reps[to];
        }

        Node parent(const Node& node) const
        {
            return reps[node];
        }

    private:
        std::unordered_map<Node, Node> reps;
};
