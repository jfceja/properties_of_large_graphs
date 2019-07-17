#include "graph.h"
#include <random>
#include <chrono>

bool bernoulli_prob(double prob, std::mt19937& rng) {
	std::bernoulli_distribution gen(prob);
	return gen(rng);
}

void iterate_previous(int m_id, std::mt19937& rng, int d, int& num_added, Graph& g) {
	for (int node_consider = 0; node_consider < m_id; ++node_consider) {
		if (num_added >= d) {
			break;
		}
		double prob = g.get_degree(node_consider);
		prob /= g.get_degree();
		bool add_edge = bernoulli_prob(prob, rng);
		if (add_edge) {
			if (g.add_edge(m_id, node_consider)) {
				++num_added;
			}
		}
	}
}

Graph create_barabasi_albert_graph(int n, int d) {
	Graph graph;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::vector<int> M (2*n*d, -1); // array of edges chosen so far
	std::mt19937 rng = std::mt19937(seed);

	for (int v = 0; v < n; ++v) {
		graph.add_vertex();
		for (int i = 0; i < d; ++i) {
			M[2*(v*d+i)] = v + Graph::offset();
			int upper_bound = 2*(v*d + i) - 1;
			if (upper_bound < 0) {
				upper_bound = 0;
			}
			std::uniform_int_distribution<int> dist(0, upper_bound);
			int r = dist(rng);
			M[2*(v*d+i) + 1] = M[r];
		}
	}
	for (int i = 0; i < n*d; ++i) {
		graph.add_edge(M[2*i], M[2*i + 1]);
	}
	return graph;
}