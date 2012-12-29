#include <vector>

#include <iostream>

#include <boost/foreach.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;

typedef adjacency_list<vecS, vecS, directedS, no_property,
		       property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					 property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;


void add_biedge(int from, int to, int cap_to, Graph& graph) {
    property_map<Graph, edge_capacity_t>::type
	capacity = get(edge_capacity, graph);

    property_map<Graph, edge_reverse_t>::type
	reverese_edge = get(edge_reverse, graph);

    Edge edge, redge; bool inserted;
    tie(edge, inserted) = add_edge(from , to, graph);
    tie(redge, inserted) = add_edge(to, from, graph);

    capacity[edge] = cap_to;
    capacity[redge] = 0;

    reverese_edge[edge] = redge;
    reverese_edge[redge] = edge;
}

int main(int argc, char *argv[]) {
    int TC; cin >> TC;

    for (int tc = 0; tc < TC; ++tc) {
	//n - #verticies
	//m - #edges
	//s - #shops
	int n,m,s; cin >> n >> m >> s;

	Graph graph(2*n + 1);
	const int SOURCE = 0;
	const int SINK = n + 2*m;

	for (int i = 0; i < s; ++i) {
	    int v0; cin >> v0;
	    add_biedge(v0, SINK, 1, graph);
	}

	int j = 0;
	for (int i = 0; i < m; ++i) {
	    int v0,v1; cin >> v0 >> v1;

	    add_biedge(v0, n + j, 1, graph);
	    add_biedge(v1, n + j, 1, graph);

	    add_biedge(n + j, n + j + 1, 1, graph);

	    add_biedge(n + j + 1, v0, 1, graph);
	    add_biedge(n + j + 1, v1, 1, graph);
	    j += 2;
	}

	long flow = push_relabel_max_flow(graph, SOURCE, SINK);

	if(flow == s) {
	    cout<<"yes\n";
	}
	else if(flow < s) {
	    cout<<"no\n";
	}
	else {
	    throw int();
	}
    }

    return 0;
}
