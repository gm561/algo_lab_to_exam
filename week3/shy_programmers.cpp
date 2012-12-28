#include <iostream>

#include <boost/foreach.hpp>

#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list <vecS, vecS, undirectedS,
			 no_property, no_property > Graph;

typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;

int main(int argc, char *argv[]) {

    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    for(int tc = 0; tc < TC; ++tc) {
	int n,m; cin >> n >> m;
	Graph graph(n+1);
	for(int i = 0; i < m; ++i) {
	    int v0,v1; cin >> v0 >> v1;
	    add_edge(v0, v1, graph);
	}

	for(int i = 0; i < n; ++i) {
	    add_edge(i, n, graph);
	}

	if(boyer_myrvold_planarity_test(graph)) {
	    cout << "yes\n";
	}
	else {
	    cout<< "no\n";
	}
    }

    return 0;
}
