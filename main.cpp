#include "union_find.hpp"
#include "graph.hpp"
#include "shortest_path.hpp"
#include "connected_components.hpp"

int main()
{
    graph<char, double> g1;
    g1.add_edge('A', 'B', 3);
    g1.add_edge('A', 'H', 4);
    g1.add_edge('H', 'F', 9);
    g1.add_edge('H', 'C', 8);
    g1.add_edge('B', 'C', 1);
    g1.add_edge('B', 'D', 5);
    g1.add_edge('D', 'E', 3);
    g1.add_edge('E', 'F', 1);

    auto cnt1 = connected_components(g1); 
    std::cout << "number of connected components: " << cnt1 << std::endl;

    graph<int, double> g2;

    // First connected component
    g2.add_edge(1, 5, 4);
    g2.add_edge(1, 3, 2);
    g2.add_edge(5, 3, 2);
    g2.add_edge(5, 7, 2);
    g2.add_edge(5, 9, 4);

    // Second connected component
    g2.add_edge(2, 4, 2);
    
    // Third connected component
    g2.add_edge(8, 6, 2);
    g2.add_edge(6, 10, 4);

    g2.spanning_tree();

    // auto cnt2 = connected_components(g2); 
    // std::cout << "number of connected components: " << cnt2 << std::endl;

    // const auto& deg_seq = g2.degree_sequence();
    // for(const auto& [vertex, degree] : deg_seq)
    // {
    //     std::cout << "\"" << vertex << "\": " << degree << ", "; 
    // }
    // std::cout << std::endl;

    return 0;
}
