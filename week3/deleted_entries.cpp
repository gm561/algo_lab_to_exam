#include <iostream>
#include <queue>

#include <boost/foreach.hpp>

#include <boost/graph/connected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list <vecS, vecS, undirectedS,
			 no_property, property < edge_weight_t, int > > Graph;

typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    for(int tc = 0 ; tc < TC; ++tc) {
	int n, m; cin >> n >> m;
	Graph graph(n);
	property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, graph);
	for(int i = 0; i < m; ++i) {
	    int v0, v1; cin >> v0 >> v1;
	    Edge edge; bool inserted;
	    tie(edge, inserted) = add_edge(v0, v1, graph);
	    weightmap[edge] = 1;
	}

	if(num_vertices(graph) < 3) {
	    cout << "no\n"; continue;
	}

	std::vector<int> component(num_vertices(graph));
	int num = connected_components(graph, &component[0]);
	if(num > 1) {
	    cout << "no\n"; continue;
	}

	std::vector<Edge> spanning_tree; spanning_tree.reserve(n-1);
	kruskal_minimum_spanning_tree(graph, std::back_inserter(spanning_tree));

	vector<int> colors(n, 0);
	vector<vector<int> > ngraph(n);

	BOOST_FOREACH(Edge e, spanning_tree) {
	    int v0 = source(e, graph);
	    int v1 = target(e, graph);

	    ngraph[v0].push_back(v1);
	    ngraph[v1].push_back(v0);
	}

	queue<int> vqueue;
	vqueue.push(0);
	colors[0] = 1;
	while(!vqueue.empty()) {
	    int v = vqueue.front(); vqueue.pop();
	    BOOST_FOREACH(int vn, ngraph[v]) {
		if(colors[vn] == 0) {
		    colors[vn] = colors[v] % 2 + 1;
		    vqueue.push(vn);
		}
	    }
	}

	int color1 = 0;
	int color2 = 0;

	for(int i = 0; i < n; ++i) {
	    if(colors[i] == 1) {
		++color1;
		if(color1 > 1) {
		    colors[i] = 3;
		    break;
		}
	    }
	    else if(colors[i] == 2){
		++color2;
		if(color2 > 1) {
		    colors[i] = 3;
		    break;
		}
	    }
	    else {
//		throw int();
	    }
	}

	vector<int> colors1; colors.reserve(n);
	vector<int> colors2; colors.reserve(n);
	vector<int> colors3; colors.reserve(n);

	for(int i = 0; i < n; ++i) {
	    int c = colors[i];
	    if(c == 1) {
		colors1.push_back(i);
	    }
	    else if(c == 2) {
		colors2.push_back(i);
	    }
	    else if(c == 3) {
		colors3.push_back(i);
	    }
	    else {
		assert(false);
	    }
	}

	if(colors1.empty () || colors2.empty() || colors3.empty()) {
//	    throw int();
	}

	cout << "yes\n";
	cout << colors1.size() <<" ";
	BOOST_FOREACH(int v, colors1) {
	    cout << v << " ";
	}
	cout<< "\n" << colors2.size() << " ";
	BOOST_FOREACH(int v, colors2) {
	    cout << v << " ";
	}
	cout<<"\n" << colors3.size() << " ";
	BOOST_FOREACH(int v, colors3) {
	    cout<< v << " ";
	}
	cout << "\n";
    }

    return 0;
}
