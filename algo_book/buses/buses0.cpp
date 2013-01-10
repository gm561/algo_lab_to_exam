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

template<class V, class E> struct Graph {
    struct Ed : E {
	int v;
	Ed(E p, int w) : E(p), v(w) {}
    };
    struct Ve : V,vector<Ed> {};
    vector<Ve> g;
    Graph(int n=0) : g(n) {}
    void EdgeU(int b, int e, E d = E()) {
	Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
    }

    bool EulerU(VI &ce) {
	int v=-1;
	ce.clear();
	VI l, st(SIZE(g), 0), of(SIZE(g)+1, 0);
	REP(x, SIZE(g)) {
	    of[x+1] = of[x] + (st[x] = SIZE(g[x]));
	    if ((st[x] & 1) || (v == -1 && st[x])) v = x;
	}
	vector<bool> us(of[SIZE(g)],0);
	if (v != -1) l.PB(v);
	while(SIZE(l)) {
	    v = l.back();
	    while(st[v] && us[of[v]+st[v]-1]) --st[v];
	    if (!st[v]) {
		l.pop_back();
		ce.PB(v);
	    } else {
		int u=g[v][--st[v]].v;
		us[of[u]+g[v][st[v]].rev]=1;
		l.PB(v=u);
	    }
	}
	return 2*(SIZE(ce)-1) == of[SIZE(g)];
    }

    void Dfs(int s, VI &path) {
	path.clear();
	VI st;
	bool found = false;

	REP(i, SIZE(g)) {
	    g[i].t = 0;
	}

	st.PB(s);
	int target = -1;
	while(!st.empty() && !found) {
	    int v = st.back(); st.pop_back();

	    FOREACH(it, g[v]) {
		if(!g[it->v].t) {
		    if(g[it->v].degree % 2) {
			found = true;
			target = it->v;
		    }
		    g[it->v].s = v;
		    st.PB(it->v);
		}
	    }
	}

	assert(target != -1);
	while(target != s) {
	    path.PB(target);
	    FOREACH(it, g[target]) {
		if(it->v == g[target].s) {
		    it->visited = g[it->v][it->rev].visited = 1;
		    break;
		}
	    }

	    --g[target].degree;
	    --g[g[target].s].degree;

	    target = g[target].s;

	}

	path.PB(s);

	reverse(ALL(path));
    }

};

struct Ve {
    int rev; int visited;
};

struct Vs {
    int t; int s; int degree;
};

void algo(Graph<Vs, Ve> & graph) {
    VI degree(SIZE(graph.g), 0);

    VI odds;
    REP(i, SIZE(graph.g)) {
    	graph.g[i].degree = degree[i] = SIZE(graph.g[i]);
    	if(degree[i] % 2) {
	    odds.PB(i);
    	}
    }

    //set all edge visited on false;
    VI path; path.clear();

    if(!odds.empty())
	cout << SIZE(odds)/2 << "\n";
    else
	cout << 1 << "\n";

    int time = SIZE(odds)/2 - 1;
    while(time-- > 0) {
    	int v = odds.back(); odds.pop_back();
    	if(graph.g[v].degree % 2) {
    	    graph.Dfs(v, path);
    	    cout << SIZE(path) << " ";
    	    FOREACH(it, path) {
    		cout << *it + 1<< " ";
    	    }
    	    cout << endl;
    	}
    }


   Graph<Vs, Ve> gu(SIZE(graph.g));
    REP(i, SIZE(graph.g)) {
    	FOREACH(it, graph.g[i]) {
    	    if(!it->visited) {
    		gu.EdgeU(i, it->v);
    		graph.g[it->v][it->rev].visited = 1;
    	    }
    	}
    }

    // REP(i, SIZE(graph.g)) {
    // 	cout << "vertex " << i << " degree " << graph.g[i].degree << endl;
    // 	FOREACH(it, graph.g[i]) {
    // 	    cout << "edge " << i << " " << it->v << " visited? " <<  it->visited << endl;
    // 	}
    // }

    gu.EulerU(path);
    cout << SIZE(path) << " ";
    FOREACH(it, path) {
    	cout << *it + 1<< " ";
    }
    cout << "\n";
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int n,m; cin >> n >> m;

    Graph<Vs, Ve> graph(n);

    while(m--) {
	int v0, v1; cin >> v0 >> v1;
	graph.EdgeU(v0 - 1, v1 - 1);
    }

    algo(graph);

    return 0;
}
