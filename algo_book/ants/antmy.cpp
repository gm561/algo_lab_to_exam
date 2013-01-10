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


    void bfs(int source) {
	FOREACH(it, g){
	    it->t = it->s = -1;
	}

	queue<int> vq;
	g[source].t = 0;
	vq.push(source);
	while(!vq.empty()) {
	    int v0 = vq.front(); vq.pop();

	    FOREACH(it, g[v0]) {
		if(g[it->v].t == -1) {
		    g[it->v].s = v0;
		    g[it->v].t = g[v0].t + 1;
		    vq.push(it->v);
		}
	    }
	}

	// FOREACH(it, g) {
	//     assert(it->t != -1);
	// }
    }
};

struct Ve { int rev;};

struct Vs { int t, s;};

void mark(Graph<Vs, Ve>& graph, int v0, int t0) {
    graph.g[v0].t = t0;
    FOREACH(it, graph.g[v0]) {
	if(it->v != graph.g[v0].s && graph.g[it->v].t == INF) {
	    mark(graph, it->v, t0);
	}
    }
}

void algo() {
    int n; cin >> n;

    Graph<Vs, Ve> graph(n);

    REP(i, n - 1) {
    	int a,b; cin >> a >> b;
    	graph.EdgeU(a - 1 ,b - 1);
    }

    int k; cin >> k;
    int defence[k];
    int pos[k];

    REP(i, k) {
	int c; cin >> c;
	pos[i] = c - 1;
	defence[i] = 0;
    }

    int l; cin >> l; int t = 2;
    REP(i, l) {
//	cout << "here" << endl;
	int source; cin >> source;
	--source;

	graph.bfs(source);
	REP(j, n) {
	    graph.g[j].t = INF;
	}

	int moveable[k];
	REP(j, k) {
	    moveable[j] = j;
	    mark(graph, pos[j], 0);
	}

	int len = k;
	while(len) {
	    REP(j, len) {
		//wsumie to niepotrzebne jesli sie widzi ze tam gdzie jest biedronka
		//ida wszystkie mrowki i jesli zmarkujemy to pole to będzie wystarczająco
		if(pos[moveable[j]] == source) {
		    len = 0;
		    ++defence[moveable[j]];
		} else if(graph.g[graph.g[pos[moveable[j]]].s].t < t) {
		    moveable[j] = -1;
		}
		else if(graph.g[pos[moveable[j]]].s == source) {
		    pos[moveable[j]] = graph.g[pos[moveable[j]]].s;
		    ++defence[moveable[j]];
		    len = 0;
		}
		else {
		    pos[moveable[j]] = graph.g[pos[moveable[j]]].s;
		    mark(graph, pos[moveable[j]], -1);
		}
	    }

	    int i = 0;
	    REP(j, len) {
		if(moveable[j] != -1) {
		    moveable[i] =  moveable[j];
		    ++i;
		}
	    }

	    len = i;
	    // REP(j, len) {
	    // 	assert(moveable[j] != -1);
	    // }
	}
	++t;
    }

    REP(i,k) {
	cout << pos[i] + 1 << " " << defence[i] << "\n";
    }

}

int main(int argc, char *argv[]) {
    algo();

    return 0;
}
