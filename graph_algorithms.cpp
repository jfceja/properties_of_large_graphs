#include "graph.h"
#include <fstream>
#include <random>
#include <chrono>
#include <algorithm>

void generate_data () {
	const std::vector<int> dist_sizes {1000, 10000, 100000};
	const int upper_bound_diameter   = 5000000;
	const int upper_bound_clustering = 500000;
	const int reps = 5;
	const int d = 5;

	const std::vector<std::string> header_diameter {"diameter.csv", "Nodes", "Diameter"};
	const std::vector<std::string> header_clustering {"clustering.csv", "Nodes", "Clustering"};

	generate_data_variable_size_data(header_diameter, upper_bound_diameter, reps, d, Algorithm::Diameter);
	generate_data_variable_size_data(header_clustering, upper_bound_clustering, reps, d, Algorithm::Clustering);

	// degree distribution
	for (int sz : dist_sizes) {
		std::cout << "Degree distribution, doing size: " << sz << std::endl;
		std::string filename = "deg_distri_" + std::to_string(sz) + ".csv";
		create_empty_timings_file({filename, "Degree", "Nodes"});
		Graph g = create_barabasi_albert_graph(sz, d);
		std::vector<std::pair<int, int>> mapping_sorted;
		std::map<int, int> mapping = get_degree_distribution(g);

		for (const auto& ele : mapping) {
			mapping_sorted.push_back(std::make_pair(ele.first, ele.second));
		}
		std::sort(mapping_sorted.begin(), mapping_sorted.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b){
			return a.first < b.first;
		});
		for (const auto& ele : mapping_sorted) {
			add_timings_to_file({filename, std::to_string(ele.first), std::to_string(ele.second)});
		}
	}
}

void generate_data_variable_size_data(const std::vector<std::string>& header, int upper_bound, int reps, int d, Algorithm algo) {
	create_empty_timings_file(header);
	// Display what we are diong, ie: diameter or clustering
	std::cout << header.back() << std::endl;
	for (int sz = 10; sz <= upper_bound; sz *= 2) {
		std::cout << "Executing size: " << sz << std::endl;
		double total = 0;
		for (int rep = 0; rep < reps; ++rep) {
			Graph g = create_barabasi_albert_graph(sz, d);
			switch (algo) {
				case Algorithm::Diameter:
					total += get_diameter(g);
					break;
				case Algorithm::Clustering:
					total += get_clustering_coefficient(g);
					break;
			}
		}
		add_timings_to_file({header.front(), std::to_string(sz), std::to_string(total/reps)});
	}
}

void graph_to_file(Graph* g) {
	if (!g) {
		return;
	}
	const std::vector<std::string> node_file {"file_of_graph_node.csv", "Id", "Label"};
	const std::vector<std::string> edge_file {"file_of_graph_edge.csv", "Source", "Target", "Type"};

	create_empty_timings_file(node_file);
	create_empty_timings_file(edge_file);
	for (const auto& node_id : g->get_ids_nodes()) {
		for (const auto& node : g->get_neighbors(Node(node_id))) {
			add_timings_to_file({edge_file.front(), std::to_string(node_id), std::to_string(node.get_m_id()), "Undirected"});
		}
		add_timings_to_file({node_file.front(), std::to_string(node_id), std::to_string(node_id)});
	}
}

void create_empty_timings_file(std::vector<std::string> data) {
	std::ofstream f;
	f.open(data.front(), std::ios::trunc);
	for (unsigned int i = 1; i < data.size(); ++i) {
		f << data[i];
		if (i < data.size() - 1) {
			f << ",";
		}
	}
	f << "\n";
	f.close();
}

void add_timings_to_file(std::vector<std::string> data) {
	std::ofstream f;
	f.open(data.front(), std::ios::app);

	for (unsigned int i = 1; i < data.size(); ++i) {
		f << data[i];
		if (i < data.size() - 1) {
			f << ",";
		}
	}
	f << "\n";
	f.close();
}

int get_diameter(Graph graph) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::mt19937 rng = std::mt19937(seed);
	std::uniform_int_distribution<int> dist(0 + Graph::offset(), graph.get_num_nodes());

	int Dmax = 0;
	Diameter_result ecce =  graph.get_eccentricity(dist(rng));

	while (ecce.result > Dmax) {
		Dmax = ecce.result;
		ecce = graph.get_eccentricity(ecce.to);
	}
	return Dmax;
}

float get_clustering_coefficient(Graph graph) {
	return static_cast<float>(3 * graph.get_triangles())/graph.total_two_edge_path();
}

std::map<int, int> get_degree_distribution(Graph graph) {
	// vertex to degree mapping, we cant degree to vertex so just reverse
	std::map<int, int> pre_process = graph.vertex_to_degree_map();
	std::map<int, int> post_process;
	for (std::map<int, int>::iterator itr = pre_process.begin(); itr != pre_process.end(); ++itr) {
		post_process[itr->second]++;
	}
	return post_process;
}
Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v) {
	if (u.size() != v.size()) {
		return Graph();
	}
	Graph g;
	for (int i = 0; i < num_nodes; ++i) {
		g.add_vertex();
	}
	for (unsigned int i = 0; i < u.size(); ++i) {
		g.add_edge(u[i], v[i]);
	}
	return g;
}
