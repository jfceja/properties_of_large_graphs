#include "project3.h"
#include "node.h"
#include <string>
#include <utility>
#include <unordered_map>
#include <iostream>

struct Diameter_result {
	int from;
	int to;
	int result;
};

class Graph : public AbstractGraph {
public:
	Graph();

	int get_num_nodes();

	int get_num_edges();

	int get_degree();

	int get_degree(int u) const;

	bool is_neighbor(Node u, Node v);

	void add_vertex();

	bool add_edge(int m_id_from, int m_id_to);

	std::vector<Node> get_neighbors(Node u);

	void print_vertices() const;

	void print_edges() const;

	std::vector<int> get_ids_nodes() const;

	std::vector<std::pair<int, int>> get_node_edge_pairs() const;

	Diameter_result get_eccentricity(int from) const;

	int get_triangles();

	int two_edge_path(int m_id) const;

	int total_two_edge_path() const;

	std::map<int, Node> get_id_to_node_map();

	std::map<int, int> vertex_to_degree_map() const;

	static int offset ();
private:
	int m_nodes;

	int m_edges;

	// offset for node ID's (starts at 0)
	static const int k_offset = 1;

	std::unordered_map<int, Node> m_graph;
};

// in graph_algorithms.cpp
enum Algorithm {
	Diameter,
	Clustering
};

void generate_data();
void graph_to_file(Graph* g = NULL);
void generate_data_variable_size_data(const std::vector<std::string>& header, int upper_bound, int reps, int d, Algorithm algo);
void create_empty_timings_file(std::vector<std::string> data);
void add_timings_to_file(std::vector<std::string> data);