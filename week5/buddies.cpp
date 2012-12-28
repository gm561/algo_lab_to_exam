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

    map<string, int> interests_map;
    vector<vector<int> > interests_vector;
    vector<vector<int> > students;

    for(int tc = 0; tc < TC; ++tc) {
	//n - #students
	//c - #characteristics
	//f - #fuzzman's solution
	int n,c,f; cin >> n >> c >> f;

	interests_map.clear();
	interests_vector.clear();

	students.clear();
	students.resize(n);

	for (int i = 0; i < n; ++i) {
	    students[i].resize(n);
	}

	int nc = 0;
	for(int i = 0; i < n; ++i) {
	    string interest;
	    for(int j = 0; j < c; ++j) {
		cin >> interest;
		if(interests_map.find(interest) == interests_map.end()) {
		    interests_map.insert(make_pair(interest, nc));
		    interests_vector.push_back(vector<int>());
		    ++nc;
		}

		int number = interests_map[interest];
		BOOST_FOREACH(int k, interests_vector[number]) {
//		    cout<<k<<endl;
		    ++students[k][i];
		}
//		cout<<"konice"<<endl;

		interests_vector[number].push_back(i);
	    }
	}

	Graph graph(n);
	for(int i = 0; i < n; ++i) {
	    for(int j = 0; j < n; ++j) {
//		cout<<"Students share "<< i << " " << j << " "<<students[i][j]<<endl;
		if(students[i][j] > f) {
		    add_edge(i, j, graph);
		}
	    }
	}

	vector<Vertex> mate(n);
	edmonds_maximum_cardinality_matching(graph, &mate[0]);

	bool solution = true;
	BOOST_FOREACH(Vertex v, mate) {
	    if(v == NULL_VERTEX) {
		solution = false;
		break;
	    }
	}

	if(solution) {
	    cout<<"not optimal\n";
	}
	else {
	    cout<<"optimal\n";
	}
    }

    return 0;
}
