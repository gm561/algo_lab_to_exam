#include <iostream>
#include <vector>

#define PB(x) push_back(x)
#define VI vector<int>
#define SIZE(x) (int)x.size()
#define REP(x, n) for(int x = 0; x < (n); ++x)

using namespace std;


template<class V, class E> struct Graph {
    struct Ed : E {
	int v;
	Ed(E p, int w) : E(p), v(w) {}
    };

    struct Ve : V, vector<Ed> {};
    vector<Ve> g;
    Graph(int n = 0) : g(n) {}

    void EdgeU(int b, int e, E d = E()) {
	Ed eg(d,e); eg.rev = SIZE(g[e]) + (b==e); g[b].PB(eg);
	eg.rev = SIZE(g[eg.v = b]) - 1; g[e].PB(eg);
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

struct Ve{int rev;};
struct Vs{};


void algo(int tc) {
    int n; cin >> n;
    const int NC = 50;
    Graph<Vs, Ve> graph(n + NC);

    for (int i = 0; i < n; ++i) {
	int a,b; cin >> a >> b;

	graph.EdgeU(a - 1, i + NC);
	graph.EdgeU(b - 1, i + NC);
    }

    VI path; //path.reserve(2*n);
    graph.EulerU(path);

    cout << "Case #" << tc << "\n";

    if(path.front() == path.back()) {
	int sync = 0;
	for(int i = 0; i < SIZE(path) - 1; ++i) {
	    if(path[i] < 50) {
		cout << path[i] + 1<< " " ;
	    }
	    else {
		    cout << path[i + 1] + 1 << " " ;
	    }

	    ++sync;
	    if(sync == 2) {
		sync = 0;
		cout << "\n";
	    }
	}
    }
    else {
	cout << "some beads may be lost\n";
    }

    cout << "\n";
}

int main(int argc, char *argv[]) {
    int tc; cin >> tc;
    int n = tc;
    while(tc--) {
	algo(n - tc);
    }

    return 0;
}
