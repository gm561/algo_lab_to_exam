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

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    for(int tc = 0; tc < TC; ++tc) {
	int p,l; cin >> p >> l;

	Graph graph(p + 3);

	//source p
	const int SOURCE = p;
	//sink p+1
	const int SINK = p + 1;
	//phantom soldiers p+2
	const int PHANTOM_SINK = p + 2;

	long desired_flow = 0L;

	//g number of soldiers present
	//required number of soldiers
	for (int i = 0; i < p; ++i) {
	    long g,d; cin >> g >> d;
	    add_biedge(SOURCE, i, g, graph);
	    add_biedge(i, SINK, d, graph);

	    desired_flow += d;
	}

	long total_phantom = 0L;
	//f - from, t - to, c - min, C - max
	for (int i = 0; i < l; ++i) {
	    long f,t,c,C; cin >> f >> t >> c >> C;
//	    cout<<"f " <<f<< " t " << t << " c "<<c << " C "<<C<<endl;
	    add_biedge(f, t, C - c, graph);

	    add_biedge(SOURCE, t, c, graph);
	    add_biedge(f, PHANTOM_SINK, c, graph);

	    total_phantom += c;
	}

	desired_flow += total_phantom;
	add_biedge(PHANTOM_SINK, SINK, total_phantom, graph);

	long flow = push_relabel_max_flow(graph, SOURCE, SINK);

	    // cout<<"Desired flow " << desired_flow <<endl;
	    // cout<<"Flow to big " << flow << endl;

	if(flow == desired_flow) {
	    cout << "yes\n";
	}
	else if(flow > desired_flow) {
	    // cout<<"Desired flow " << desired_flow <<endl;
	    // cout<<"Flow to big " << flow << endl;
	    throw int();
	}
	else {
	    cout << "no\n";
	}
    }

    return 0;
}
