#include <iostream>
#include <vector>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>

#include <boost/foreach.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, no_property> Graph;

int main(int argc, char *argv[]) {

    int TC; cin >> TC;
    vector<vector<int> > elections;

    for(int tc = 0; tc < TC; ++tc) {
	int n; cin >> n;
	elections.resize(n);
	for (int i = 0; i < n; ++i) {
	    elections[i].resize(n-1);
	}

	for (int i = 0; i < n; ++i) {
	    for (int j = 0; j < n - 1; ++j) {
		cin >> elections[i][j];
	    }
	}

	int T = 0;
	Graph graph(n);
	for (int i = 0; i < n - 1; ++i) {
	    for (int j = 0; j < n; ++j) {
		add_edge(j, elections[j][i], graph);
	    }

	    if(!boyer_myrvold_planarity_test(graph)) {
		break;
	    }
	    else {
		++T;
	    }
	}

	cout << T << "\n";
    }


    return 0;
}
