#include <iostream>

#include <boost/foreach.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>
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


typedef adjacency_list <vecS, vecS, undirectedS, no_property, no_property > UndirectedGraph;

typedef graph_traits <UndirectedGraph>::edge_descriptor UEdge;
typedef graph_traits <UndirectedGraph>::vertex_descriptor UVertex;


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

bool isEuleran(const UndirectedGraph& graph,
	       const vector<int>& sweepers,
	       const vector<int>& doors,
	       int n) {

    for(int i = 0; i < n; ++i) {
	Vertex v0 = vertex(i, graph);
	size_t vdegree = in_degree(v0, graph);

	if((vdegree + sweepers[i] + doors[i] ) % 2 != 0) {
	    return false;
	}
    }

    std::vector<int> component(num_vertices(graph));
    int num = connected_components(graph, &component[0]);

    std::vector<int> accessible_components_sweepers(num);
    std::vector<int> accessible_components_doors(num);

    for(int i = 0; i < n; ++i) {
	if(sweepers[i]) {
	    ++accessible_components_sweepers[component[i]];
	}

	if(doors[i]) {
	    ++accessible_components_doors[component[i]];
	}
    }

    for (int i = 0; i < num; ++i) {
	if(accessible_components_sweepers[i] != accessible_components_sweepers[i] ||
	    accessible_components_sweepers[i] == 0) {
	    //number of vertex in this component is more than one
	    int nver = 0;
	    for (int j = 0; j < n; ++j) {
		if(component[j] == i) {
		    ++nver;
		    if(nver > 1) {
			break;
		    }
		}
	    }

	    if(nver > 1) {
		return false;
	    }
	}
    }

    return true;
}

void algo() {
    int n,m,s ;cin >> n >> m >> s;

    vector<int> sweepers(n);
    vector<int> doors(n);

    for (int i = 0; i < s; ++i) {
	int v0; cin >> v0;
	++sweepers[v0];
    }

    for (int i = 0; i < s; ++i) {
	int v0; cin >> v0;
	++doors[v0];
    }

    const int SOURCE = n;
    const int SINK =  n + 1;
    const int SWEEP_SOURCE = n + 2;

    Graph graph(n + 3);
    UndirectedGraph ugraph(n);

    for (int i = 0; i < m; ++i) {
	int v0, v1; cin >> v0 >> v1;

	add_biedge(v0, v1, 1, graph);
	add_biedge(v1, v0, 1, graph);

	add_edge(v0, v1, ugraph);
    }

    if(!isEuleran(ugraph, sweepers, doors, n)) {
	cout << "no\n";
	return;
    }

    add_biedge(SOURCE, SWEEP_SOURCE, s, graph);

    for(int i = 0; i < n; ++i) {
	if(sweepers[i]) {
	    add_biedge(SWEEP_SOURCE, i, sweepers[i], graph);
	}

	if(doors[i]) {
	    add_biedge(i, SINK, doors[i], graph);
	}
    }


    long flow = push_relabel_max_flow(graph, SOURCE, SINK);

    cout << ((flow == s) ? "yes\n" : "no\n");
}

int main(int argc, char *argv[]) {
    int TC; cin >> TC;

    for (int tc = 0; tc < TC; ++tc) {
	algo();
    }

    return 0;
}
