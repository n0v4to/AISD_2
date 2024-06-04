#include <iostream>
#include "Graph.h"
#include <vector>


int main() {
    
    Graph<int, double> graph;

    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_vertex(4);
    graph.add_vertex(5);

    graph.add_edge(2, 5, 2.0);
    graph.add_edge(1, 5, 8.0);
    graph.add_edge(1, 3, 1.0);
    graph.add_edge(3, 5, 10.0);
    graph.add_edge(3, 4, 3.0);
    graph.add_edge(3, 2, 1.0);
    graph.add_edge(2, 3, 7.0);
    graph.add_edge(4, 5, 9.0);
    graph.add_edge(5, 1, 5.0);

    graph.print_edges();

    auto path = graph.shortest_path(1, 5);
    std::cout << "Shortest path from 1 to 5: ";
    for (const auto& edge : path) {
        std::cout << "From: " << edge.from << " To: " << edge.to << " Weight: " << edge.distance << std::endl;
    }
    std::cout << "Center: " << graph.find_optimal_warehouse() << std::endl;

    return 0;
}