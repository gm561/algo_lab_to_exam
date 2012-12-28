#include <iostream>
#include <vector>
#include <climits>
#include <queue>

#include <boost/foreach.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>

#define SIZE(x) (int)x.size()

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;

typedef adjacency_list<vecS, vecS, directedS, no_property,
		       property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					 property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;

    for (int tc = 0; tc < TC; ++tc) {
	int n, m; cin >> n >> m;

	Graph graph(n);

	EdgeCapacityMap capacity = get(edge_capacity, graph);
	ReverseEdgeMap reverse_edge = get(edge_reverse, graph);
	property_map<Graph, edge_residual_capacity_t>::type
	    residual_capacity = get(edge_residual_capacity, graph);

	for (int i = 0; i < m; ++i) {
	    int v0, v1, c; cin >> v0 >> v1 >> c;
	    Edge edge, redge; bool inserted;

	    tie(edge, inserted) = add_edge(v0, v1, graph);
	    tie(redge, inserted) = add_edge(v1, v0, graph);

	    capacity[edge] = c;
	    capacity[redge] = 0;

	    reverse_edge[edge] = redge;
	    reverse_edge[redge] = edge;

	    tie(edge, inserted) = add_edge(v0, v1, graph);
	    tie(redge, inserted) = add_edge(v1, v0, graph);

	    capacity[edge] = 0;
	    capacity[redge] = c;

	    reverse_edge[edge] = redge;
	    reverse_edge[redge] = edge;

	}

	vector<int> components(num_vertices(graph));
	int num = connected_components(graph, &components[0]);

	vector<int> owned_componets; owned_componets.reserve(n);

	long min_cut = 0;
	if(num > 1) {
	    for (int i = 0; i < SIZE(components); ++i) {
		if(components[i] == 0) {
		    owned_componets.push_back(i);
		}
	    }
	}
	else {
	    Vertex vsource = vertex(0, graph);
	    Vertex vbest_sink = -1;
	    min_cut = LONG_MAX;
	    for(int i = 1; i < n; ++i) {
		Vertex vsink = vertex(i, graph);
//		cout << "Vertex " << sink << endl;
		long flow = push_relabel_max_flow(graph, vsource, vsink);

//		cout << "Flow " << flow << endl;
		if(flow < min_cut) {
		    min_cut = flow;
		    vbest_sink = i;
		    owned_componets.clear();
		}
	    }

//	    cout<<"best sink " << best_sink << endl;
	    push_relabel_max_flow(graph, vsource, vbest_sink);

	    typedef adjacency_list<vecS, vecS, bidirectionalS> SimpleGraph;
	    SimpleGraph simple_graph(n);
	    graph_traits<Graph>::edge_iterator ei, ei_end;

	    for (tie(ei, ei_end) = edges(graph); ei != ei_end; ++ei) {
		if(residual_capacity[*ei] > 0) {
		    add_edge(source(*ei, graph), target(*ei, graph), simple_graph);
		}
	    }

	    vector<int> components(num_vertices(simple_graph));
	    connected_components(simple_graph, &components[0]);
	    for (int i = 0; i < SIZE(components); ++i) {
		if(components[i] == 0) {
		    owned_componets.push_back(i);
		}
	    }
	}

	cout<< min_cut << "\n" << SIZE(owned_componets) << " ";
	BOOST_FOREACH(int comp, owned_componets) {
	    cout<< comp << " ";
	}
	cout<< "\n";
    }

    return 0;
}
