#include <iostream>
#include <vector>
#include <stack>

#define FOR(x, b, e) for(int x=b; x<=(e); ++x)
#define FORD(x, b, e) for(int x=b; x>=(e); ––x)
#define REP(x, n) for(int x=0; x<(n); ++x)
#define VAR(v,n) typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

using namespace std;

void BFS(const vector<vector<int> >& graph,
	 vector<int>& visited,
	 int source) {

    stack<int> vstack;
    vstack.push(source);
    visited[source] = 1;
    while(!vstack.empty()) {
	int cv = vstack.top(); vstack.pop();

	FOREACH(v, graph[cv]) {
	    if(!visited[*v]) {
		vstack.push(*v);
		visited[*v] = 1;
	    }
	}
    }
}

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int n,m;
    vector<vector<int> > graph;
    vector<int> visited;
    while(cin>>n>>m) {
	graph.clear();
	graph.resize(n);

	visited.clear();
	visited.resize(n);

	for(int i = 0; i < m; ++i) {
	    int v0,v1; cin>>v0>>v1;
	    --v0;
	    --v1;
	    graph[v0].push_back(v1);
	    graph[v1].push_back(v0);
	}

	int k = 0;
	while(true) {
	    int source = -1;
	    for(int i = 0; i < n; ++i) {
		if(!visited[i]) {
		    source = i;
		    break;
		}
	    }

	    if(source != -1) {
		BFS(graph, visited, source);
		++k;
	    }
	    else {
		break;
	    }
	}

	cout<<m - n  + k + 1<<"\n";
    }

    return 0;
}
