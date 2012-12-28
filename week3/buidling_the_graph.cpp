#include <iostream>

#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/foreach.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/visitors.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list < vecS, vecS, undirectedS,
			 no_property, property < edge_weight_t, int > > Graph;
typedef graph_traits < Graph >::edge_descriptor Edge;
typedef graph_traits < Graph >::vertex_descriptor Vertex;
typedef std::pair<int, int> E;


int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;

    for(int tc = 0; tc < TC; ++tc) {
	size_t n,m; cin >> n >> m;

	Graph graph(n);
	property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, graph);
	for(size_t i = 0; i < m; ++i) {
	    int v0,v1,w; cin >> v0 >> v1 >> w;
	    Edge e; bool inserted;

	    boost::tie(e, inserted) = add_edge(v0, v1, graph); assert(inserted);
	    weightmap[e] = w;
	}

	std::vector<Edge> spanning_tree;
	kruskal_minimum_spanning_tree(graph, std::back_inserter(spanning_tree));

	int weight_sum = 0;
	BOOST_FOREACH(Edge e, spanning_tree) {
	    weight_sum += get(edge_weight, graph, e);
	}

	Vertex source  = vertex(0, graph);
        vector<size_t> distance(num_vertices(graph));
	vector<Vertex> predecessors(num_vertices(graph));

	dijkstra_shortest_paths(graph, source,
				predecessor_map(&predecessors[0]).distance_map(&distance[0]));

	vector<size_t>::iterator it = max_element(distance.begin(), distance.end());

        cout<< weight_sum << " " << *it << "\n";
    }

    return 0;
}
