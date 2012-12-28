#include <iostream>
#include <map>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <boost/foreach.hpp>

#define SIZE(x) (int) x.size()

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS> Graph;

typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;

static const Vertex NULL_VERTEX = graph_traits<Graph>::null_vertex();

int main(int argc, char *argv[]) {
    int TC; cin >> TC;

    vector<vector<int> > input;
    for(int tc = 0; tc < TC; ++tc) {
	int w,h; cin >> w >> h;
	input.resize(w);
	for (int i = 0; i < w; ++i) {
	    input[i].resize(h);
	}

	int n = 0;
	for(int j = 0; j < h; ++j) {
	    for(int i = 0; i < w; ++i) {
		char c; cin >> c;
		if(c == '.') {
		    input[i][j] = n;
		    ++n;
		}
		else {
		    input[i][j] = -1;
		}
	    }
	}

	Graph graph(n);
	    for (int j = 0; j < h; ++j) {
		for(int i = 0; i < w; ++i) {
		    if(input[i][j] != -1) {
//			cout << "Vertex " << input[i][j] << " connected "<<endl;
			if(i - 1 >= 0 && input[i-1][j] != -1) {
			    add_edge(input[i][j], input[i-1][j], graph);
//			    cout<<  input[i-1][j] << endl;
			}

			if(j - 1 >= 0 && input[i][j-1] != -1) {
			    add_edge(input[i][j], input[i][j-1], graph);
//			    cout<<  input[i][j-1] << endl;
		    }
		}
	    }
	}

	vector<Vertex> mate(n);
	edmonds_maximum_cardinality_matching(graph, &mate[0]);

	bool solution = true;
	for (int i = 0; i < n; ++i) {
	    if(mate[i] == NULL_VERTEX) {
//		cout << i << endl;
		solution = false;
	    }
	}

	cout << ((solution) ? "yes\n" : "no\n") ;
    }

    return 0;
}
