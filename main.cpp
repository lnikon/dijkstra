#include "graph.hpp"

int main()
{
    graph<char, double> g;
    g.add_edge('A', 'B', 3);
    g.add_edge('A', 'H', 4);
    g.add_edge('H', 'F', 9);
    g.add_edge('H', 'C', 8);
    g.add_edge('B', 'C', 1);
    g.add_edge('B', 'D', 5);
    g.add_edge('D', 'E', 3);
    g.add_edge('E', 'F', 1);

    char source = 'A';
    std::map<char, double> min_distance;
    std::map<char, char> previous;

    shortest_path(g, source, min_distance, previous);

    for(auto const & kvp : min_distance)
    {
        std::cout << source << " -> " 
            << kvp.first << " : " 
            << kvp.second << '\t';

        print_path(build_path(previous, kvp.first));
    }

    return 0;
}
