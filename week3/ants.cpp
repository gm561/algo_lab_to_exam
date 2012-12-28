#include <iostream>

#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/foreach.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/visitors.hpp>
#include <boost/foreach.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list <vecS, vecS, undirectedS,
			 no_property, property < edge_weight_t, int > > Graph;

typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;

int main(int argc, char *argv[]) {

    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    for(int tc = 0; tc < TC; ++tc) {
	//numbe of edges and verticies
	int n, m; cin >> n >> m;
	//number of species
	int s; cin >> s;
	//start tree, finish tree
	int a,b; cin >> a >> b;

	vector<Graph> graphs;
	vector<property_map<Graph, edge_weight_t>::type> weightmaps;

	for(int i = 0; i < s; ++i) {
	    graphs.push_back(Graph(n));
	    weightmaps[i] = get(edge_weight, graphs[i]);
	}

	for(int i = 0; i < m; ++i) {
	    int v0, v1; cin >> v0 >> v1;
	    for(int j = 0; j < s; ++j) {
		bool inserted; Edge edge;
		tie(edge, inserted) = add_edge(v0 , v1, graphs[j]);

		int weight; cin >> weight;
		weightmaps[j][edge] = weight;
	    }
	}
	vector<Vertex> sources; sources.reserve(n);
	for(int i = 0; i < s; ++i) {
	    int v0; cin >> v0;
	    Vertex source = vertex(v0, graphs[i]);
	    sources.push_back(source);
	}

	Graph combined_graph(n);
	property_map<Graph, edge_weight_t>::type weight_map_comb =
	    get(edge_weight, combined_graph);

	vector<vector<Edge> > spanning_trees; spanning_trees.resize(s);
	for(int i = 0; i < s; ++i) {
	    spanning_trees[i].reserve(n);
	    kruskal_minimum_spanning_tree(graphs[i], std::back_inserter(spanning_trees[i]));

	    BOOST_FOREACH(Edge edge, spanning_trees[i]) {
	    	Edge iedge; bool inserted;
	    	tie(iedge, inserted) =
	    	    add_edge(source(edge, graphs[i]),
	    		     target(edge, graphs[i]), combined_graph);
	    	weight_map_comb[iedge] = weightmaps[i][edge];
	    }
	}

        vector<size_t> distance(num_vertices(combined_graph));
	Vertex source = vertex(a, combined_graph);
	dijkstra_shortest_paths(combined_graph, source, distance_map(&distance[0]));
	int time = distance[b];
	cout << time << "\n";
    }

    return 0;
}
