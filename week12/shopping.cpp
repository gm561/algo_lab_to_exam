#include <iostream>
#include <vector>

#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;


typedef adjacency_list<vecS, vecS, directedS, no_property,property<edge_weight_t, int> > Graph;

typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;

void algo() {
    int n; cin >> n;
    int h; cin >> h;
    int s; cin >> s;

    vector<vector<int> > nodes(n, vector<int>(n));

    for(int i = 0; i < n; i++) {
	for(int j = 0; j < n; ++j) {
	    cin >> nodes[i][j];
	}
    }

    Graph graph(n*n);
    property_map<Graph, edge_weight_t>::type weightmap;

    //set weights of the graph
    for(int i = 0; i < n; ++i) {
    	for(int j = 0; j < n; ++j) {
    	    Vertex v0 = vertex(i*n + j, graph);
    	    if(j - 1 >= 0) {
    		Vertex v1 = vertex(i*n + j - 1, graph);
    		int weight = abs(nodes[i][j-1] - nodes[i][j]);
    		Edge e0, e1; bool inserted;

    		if(nodes[i][j-1] > nodes[i][j]) {
    		    tie(e0, inserted) = add_edge(v0, v1, graph);
    		    tie(e1, inserted) = add_edge(v1, v0, graph);

    		}
    		else {
    		    tie(e0, inserted) = add_edge(v1, v0, graph);
    		    tie(e1, inserted) = add_edge(v0, v1, graph);
    		}

    		weightmap[e0] = weight;
    		weightmap[e1] = 0;
    	    }

    	    if(i - 1 >= 0) {
    	    	Vertex v1 = vertex((i-1)*n + j, graph);
    	    	int weight = abs(nodes[i-1][j] - nodes[i][j]);
    	    	Edge e0, e1; bool inserted;

    	    	if(nodes[i-1][j] > nodes[i][j]) {
    	    	    tie(e0, inserted) = add_edge(v0, v1, graph);
    	    	    tie(e1, inserted) = add_edge(v1, v0, graph);
    	    	}
    	    	else {
    	    	    tie(e0, inserted) = add_edge(v1, v0, graph);
    	    	    tie(e1, inserted) = add_edge(v0, v1, graph);
    	    	}

    	    	weightmap[e0] = weight;
    	    	weightmap[e1] = 0;
    	    }
    	}
    }

    std::vector<int> d(n*n, std::numeric_limits<int>::max());
    vector<vector<int > > D(n*n, vector<int>(n*n));

    floyd_warshall_all_pairs_shortest_paths(graph, D, distance_map(&d[0]));

    vector<pair<int,int> > houses;
    for(int i = 0; i < h; ++i) {
    	int x,y; cin >> x >> y;
    	houses.push_back(make_pair(x,y));
    }

    vector<pair<int,int> > stores;
    for(int i = 0; i < s; ++i) {
    	int x,y; cin >> x >> y;
    	stores.push_back(make_pair(x,y));
    }

    // cout << D[3*n + 0][2*n + 0] << endl;
    // cout << D[2*n + 0][2*n + 1] << endl;
    // cout << D[2*n + 1][2*n + 2] << endl;
    // cout << D[3*n + 0][2*n + 2] << endl;
//    	cout << "store " << sy << " " << sx << endl;
//    	    cout << "house " << hx << " " << hy << endl;


    int max = 0;
    for(int i = 0; i < h; ++i) {
	int hx,hy;
	tie(hy,hx) = houses[i];
	int min = INT_MAX;

	for(int j = 0; j < s; ++j) {
	    int sx,sy;
	    tie(sy,sx) = stores[j];

    	    if(D[sx + sy*n][hx + hy*n] < min) {
    		min = D[sx + sy*n][hx + hy*n];
    	    }
    	}

	if(min > max) {
	    max = min;
	}
    }

    cout << max << "\n";
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    for (int tc = 0; tc < TC; ++tc) {
	algo();
    }

    return 0;
}
