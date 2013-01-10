#include <iostream>
#include <vector>

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

    tie(edge, inserted) = add_edge(from, to, graph);
    tie(redge, inserted) = add_edge(to, from, graph);

    capacity[edge] = cap_to;
    capacity[redge] = 0;

    reverese_edge[edge] = redge;
    reverese_edge[redge] = edge;
}


void algo() {
    int w,n; cin >> w >> n;

    Graph graph(w + w + 2);

    const int SOURCE = w + 1;
    const int SINK = w;

    for (int i = 1; i < w; ++i) {
	add_biedge(i, i + w + 1, 1, graph);
    }

    for (int i = 0; i < n; ++i) {
	int x,y; cin >> x >> y;
	add_biedge(min(x,y) + w + 1, max(x,y), 1, graph);
    }

    long flow = push_relabel_max_flow(graph, SOURCE, SINK);

    cout << flow << "\n";
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int tc; cin >> tc;

    while(tc--) {
	algo();
    }

    return 0;
}
