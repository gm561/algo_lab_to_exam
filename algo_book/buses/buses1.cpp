#include <cassert>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

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
};

struct Ve {
    int rev;
};

struct Vs {

};

void algo(Graph<Vs,Ve> &g) {
    //connect all odd degree verticies with auxiliary vertex 0
    REP(i, SIZE(g.g) - 1) {
	if(SIZE(g.g[i+1]) & 1) {
	    g.EdgeU(i+1, 0);
	}
    }

    VI path;
    g.EulerU(path);

    int i = 0;
    vector<VI> nums;
    nums.PB(VI());
    FOREACH(it, path) {
	if(*it == 0) {
	    if(SIZE(nums[i])) {
		nums.PB(VI());
		++i;
	    }
	}
	else {
	    nums[i].PB(*it);
	}
    }

    i = (SIZE(nums.back())) ? i + 1: i;
    cout << i << "\n";
    FOREACH(it, nums) {
	if(SIZE((*it))) {
	    cout << SIZE((*it)) << " ";
	    FOREACH(it2, *it) {
		cout << *it2<< " ";
	    }
	    cout << "\n";
	}
    }
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int n,m; cin >> n >> m;

    Graph<Vs, Ve> graph(n + 1);

    while(m--) {
	int v0, v1; cin >> v0 >> v1;
	graph.EdgeU(v0, v1);
    }

    algo(graph);

    return 0;
}
