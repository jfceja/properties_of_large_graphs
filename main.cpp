#include "graph.h"
#include <iostream>
#define MANUAL_DRIVER 0

int main() {
	if (MANUAL_DRIVER) {
		// this is for manual testing
		Graph graph;

		for (int i =  0; i < 4; ++i) {
			graph.add_vertex();
		}
		graph.add_edge(1, 2);
		graph.add_edge(2, 3);
		graph.add_edge(3, 4);
		graph.add_edge(4, 1);

		graph.print_vertices();
		graph.print_edges();
	} else {
		// this is to create the .csv files for the graph (basically generate the data)
		Graph graph = create_barabasi_albert_graph(1000, 5);
		graph_to_file(&graph);
		generate_data();
	}
	return 0;
}