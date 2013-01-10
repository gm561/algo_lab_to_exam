#include <cassert>
#include <queue>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>

using namespace std;

typedef vector<int> VI;
typedef long long LI;

#define FOR(x,b,e) for(int x = b; x<= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < n; ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) c.begin(), c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second

const int INF = 1000000001;

template <class V, class E>
struct Graph {
    struct Ed : E {
	int v;
	Ed(E p, int w) : E(p), v(w) { }
    };

    struct Ve : V, vector<Ed> {};

    vector<Ve> g;

    Graph(int n = 0) : g(n) {}

    void EdgeD(int b, int e, E d = E()) {
	g[b].PB(Ed(d,e));
    }

    void EdgeU(int b, int e, E d = E()) {
	Ed eg(d, e);
	eg.rev = SIZE(g[e]) + (b == e);
	g[b].PB(eg);
	eg.rev = SIZE(g[eg.v = b]) - 1;
	g[e].PB(eg);
    }

    bool EulerD(VI &route) {
	VI in_degree(SIZE(g), 0);
	VI out_degree;

	FOREACH(it, g) {
	    out_degree.PB(SIZE((*it)));
	    FOREACH(it2, *it) {
		++in_degree[it2->v];
	    }
	}

	int v_start = -1;
	int v_end = -1;
	REP(x, SIZE(g)) {
	    if(SIZE(g[x]) > in_degree[x]) {
		if(v_start != -1) return false;
		v_start = x;
	    }
	    else if(SIZE(g[x]) < in_degree[x]) {
		if(v_end != -1) return false;
		v_end = x;
	    }
	}

	if(v_start == -1 || v_end == -1) return false;


	route.clear();
	stack<int> st;

	int v = v_start;
	st.push(v_start);

	while(!st.empty()) {
	    v = st.top();
	    if(!out_degree[v]) {
		st.pop();
		route.PB(v);
	    }
	    else {
		st.push(g[v][--out_degree[v]].v);
	    }
	}

	reverse(ALL(route));
	return true;
    }
};

struct Ve {
    int t;
};

struct Vs {
    int d, f, s;
};


int main(int argc, char *argv[]) {
    int n,m; cin >> n >> m;
    Graph<Vs, Ve> graph(n);
    REP(i, m) {
	int v0,v1; cin >> v0 >> v1;
	graph.EdgeD(v0, v1);
    }

    VI route;
    assert(graph.EulerD(route));
    FOREACH(it, route) {
	cout << *it << " ";
    }
    cout << endl;
    return 0;
}
