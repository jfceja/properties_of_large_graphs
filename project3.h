#include <vector>
#include <map>

#ifndef PROJECT3_H
#define PROJECT3_H

/******* NODE CLASS ********/
class Node;  


class AbstractGraph 
{
    public: 
        virtual int get_num_nodes() = 0; // number of nodes
        virtual int get_num_edges() = 0; // number of edges
        virtual bool is_neighbor(Node u, Node v) = 0 ;
        virtual std::vector<Node> get_neighbors(Node u) = 0; 

        // allows lookup of nodes from ids
        virtual std::map<int, Node> get_id_to_node_map() = 0;
};

class Graph; 
             
            
// construct a graph using num_nodes nodes and edges (ui, vi) for all i
// u and v will be the same length
// (ui, vi) are pairs of integers which can be mapped uniquely to (ui', vi'), pairs of Nodes
Graph make_graph(int num_nodes, std::vector<int> u, std::vector<int> v);


int get_diameter(Graph graph); 
float get_clustering_coefficient(Graph graph);
std::map<int, int> get_degree_distribution(Graph graph);

/******* GRAPH GENERATION FUNCTIONS ********/
Graph create_erdos_renyi_graph(int n, float p); // did NOT implement
                                                
Graph create_barabasi_albert_graph(int n, int d); 
                                                  
/******* FILE SUMMARY (SORTED BY DEPENDENCIES) 
    project3.h
    node.h
    graph.h
    graph.cpp
    graph_algorithms.cpp
    barabasi_albert.cpp (see GRAPH GENERATION FUNCTIONS section)
    run.sh 
*/
#endif