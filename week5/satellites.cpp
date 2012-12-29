#include <iostream>
#include <vector>
#include <queue>

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

    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    for (int tc = 0; tc < TC; ++tc) {
	int g,s,l; cin >> g >> s >> l;
	Graph graph(g + s);

	for (int i = 0; i < l; ++i) {
	    int v0, v1; cin >> v0 >> v1;
	    add_edge(v0, v1 + g, graph);
	}

	vector<Vertex> mate(g + s);
	edmonds_maximum_cardinality_matching(graph, &mate[0]);

	vector<Vertex> unmatched;
	for(int i = 0; i < g + s; ++i) {
	    if(mate[i] == NULL_VERTEX) {
		unmatched.push_back(i);
	    }
	}

	vector<Vertex> satellites;
	vector<Vertex> stations;

	//perfect matching
	if(unmatched.empty()) {
	    stations.reserve(g);
	    for(int i = 0; i < g; ++i)  {
		stations.push_back(i);
	    }
	}
	else {
	    vector<Vertex> visited(g + s);
	    queue<pair<Vertex, bool> > vqueue;

	    BOOST_FOREACH(int v0, unmatched) {
		vqueue.push(make_pair(v0, false));
		visited[v0] = 1;
	    }

	    graph_traits<Graph>::adjacency_iterator ai, ai_end;
	    while(!vqueue.empty()) {
		Vertex v0; bool value;
		tie(v0, value) = vqueue.front(); vqueue.pop();

		if(value) {
		    ((int)v0 < g) ? stations.push_back(v0) : satellites.push_back(v0 - g);

		    if(!visited[mate[v0]]) {
			vqueue.push(make_pair(mate[v0], !value));
			visited[mate[v0]] = 1;
		    }
		}
		else {
		    for (tie(ai, ai_end) = adjacent_vertices(v0, graph);
			 ai != ai_end; ++ai) {
			if(!visited[*ai]) {
			    vqueue.push(make_pair(*ai, true));
			    visited[*ai] = 1;
			}
		    }
		}

		//some vertices not reached
		if(vqueue.empty()) {
		    for(int i = 0; i < SIZE(visited); ++i) {
			if(!visited[i]) {
			    visited[i] = 1;
			    vqueue.push(make_pair(i, true));
			    break;
			}
		    }
		}
	    }
	}

	sort(stations.begin(), stations.end());
	sort(satellites.begin(), satellites.end());

	cout << stations.size() << " " << satellites.size() << "\n";
	BOOST_FOREACH(int k, stations) {
	    cout << k << " " ;
	}

	BOOST_FOREACH(int k, satellites) {
	    cout << k << " " ;
	}

	cout << "\n";
    }

    return 0;
}
