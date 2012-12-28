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

    tie(edge, inserted) = add_edge(from, to, graph);
    tie(redge, inserted) = add_edge(to, from, graph);

    capacity[edge] = cap_to;
    capacity[redge] = 0;

    reverese_edge[edge] = redge;
    reverese_edge[redge] = edge;
}

struct Knight {
    int x,y;

    Knight(int x_, int y_) : x(x_), y(y_) {}
};



int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    vector<Knight> knights;
    for (int tc = 0; tc < TC; ++tc) {
	//m x n dimensions of the cave
	//k - #knights
	int m,n,k; cin >> m >> n >> k;

	knights.clear();
	knights.reserve(k);
	for (int i = 0; i < k; ++i) {
	    int x,y; cin >> x >> y;
	    knights.push_back(Knight(x,y));
	}

	const int SINK = 2*m*n;
	const int SOURCE = 2*m*n+1;

	Graph graph(2*m*n + 2);
	for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < m; ++j) {
		int v0 = i*m + j;
		int v0p = v0 + m*n;
		add_biedge(v0, v0 + m*n, 1, graph);

		//up
		if( i - 1 >= 0) {
		    int v1 = (i-1)*m + j;
		    add_biedge(v0p, v1, 1, graph);
		}
		//down
		if( i + 1 < n) {
		    int v1 = (i+1)*m + j;
		    add_biedge(v0p, v1, 1, graph);
		}
		//left
		if(j - 1 >= 0) {
		    int v1 = i*m + j - 1;
		    add_biedge(v0p, v1, 1, graph);
		}
		//right
		if(j + 1 < m) {
		    int v1 = i*m + j + 1;
		    add_biedge(v0p, v1, 1, graph);
		}

		if(i == 0 || j == 0 || i == n - 1 || j == m - 1) {
		    add_biedge(v0 + m*n, SINK, 1, graph);
		}
	    }
	}

	BOOST_FOREACH(Knight k, knights) {
	    add_biedge(SOURCE, k.x + k.y * m, 1, graph);
	}

	long flow = push_relabel_max_flow(graph, SOURCE, SINK);

	cout << flow << "\n";
    }

    return 0;
}
