#include <cassert>
#include <queue>
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

    void Write() {
	REP(x, SIZE(g)) {
	    cout << x << ":";
	    FOREACH(it, g[x]) cout << " " << it->v;
	    cout << endl;
	}
    }

  void DFS(int e = -1) {
      VI st(SIZE(g));
      int t = -1 , i = 0, b = 0;
      e==-1 ? e=SIZE(g)-1 : b = e;
      REP(x,SIZE(g)) g[x].d = g[x].f = g[x].s = -1;

      FOR(s,b,e) if(g[s].d == -1) {

	  g[st[i++] = s].d = ++t; g[s].f = SIZE(g[s]);

	  while(i) {
	      int s = st[i-1];
	      if (!g[s].f) {g[s].f = ++t; --i;} else {
		  if (g[s = g[s][--g[s].f].v].d == -1) {
		      g[s].s = st[i-1];
		      g[s].f = SIZE(g[s]);
		      g[st[i++] = s].d = ++t;
		  }
	      }
	  }
      }
  }
};

struct Ve { int rev;};

struct Vs {
    int d, f, s;
    VI l;
};

void genLCA(Graph<Vs, Ve> &graph, int v) {
    if(v != 0 && !SIZE(graph.g[v].l)) {
	int c = graph.g[v].s;
	genLCA(graph, c);
	graph.g[v].l.PB(c);

	while(SIZE(graph.g[c].l) >= SIZE(graph.g[v].l)) {
	    c = graph.g[c].l[ SIZE(graph.g[v].l) - 1];
	    graph.g[v].l.PB(c);
	}
    }
}

#define Desc(n,m) (graph.g[n].d <= graph.g[m].d && graph.g[n].f >= graph.g[m].f)

int LCA(Graph<Vs, Ve> &graph, int b, int e) {
    int res = 0, p = SIZE(graph.g[b].l) - 1;

    while(!Desc(b,e)) {

	p = min(p, SIZE(graph.g[b].l) - 1);
	while(p > 0 && Desc(graph.g[b].l[p], e)) --p;

	res += (1 << p) ;
	b = graph.g[b].l[p];
    }

    return res;
}


void algo() {
    int n; cin >> n;
    Graph<Vs, Ve> graph(n);

    for(int i = 0; i < n - 1; ++i) {
	int x,y; cin >> x >> y;
	graph.EdgeU(x - 1, y - 1);
    }

    int m; cin >> m;
    int b = 1;
    int res = 0;

    graph.DFS(0);

    FOR(x, 1, n-1) genLCA(graph, x);

    for(int i = 0; i < m; ++i) {
    	int e; cin >> e;
    	res += LCA(graph, b - 1, e - 1) + LCA(graph, e - 1, b - 1);
    	b = e;
    }

    cout << res << endl;
}

int main(int argc, char *argv[]) {
    algo();

    return 0;
}
