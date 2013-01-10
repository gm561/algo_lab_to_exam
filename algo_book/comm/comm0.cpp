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
    vector<int> topoOrder;

    Graph(int n = 0) : g(n) , topoOrder(n) {}

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

    bool possible;
    void Dfs(int source, VI &cand, int i) {
	if(cand[source] == 0) {
	    int comp = ((source % 2) ? (source - 1) : (source + 1) );
	    cand[source] = -i;
	    cand[comp] = i;
	    FOREACH(it, g[comp]) {
		if(possible)
		    Dfs(it->v, cand, i);
	    }

	    if(!possible) {
		FOREACH(it, g[comp]) {
		    if(abs(cand[it->v]) == i) {
			cand[it->v] = 0;
			int comp0 = ((it->v % 2) ? (it->v - 1) : (it->v + 1) );
			cand[comp0] = 0;
		    }
		}

		cand[source] = 0;
		cand[comp] = 0;
	    }
	}
	else if(cand[source] < 0) {
	    //nothink to do
	}
	else if(cand[source] > 0) {
	    possible = false;
	}
    }

    void print(VI &cand) {
	int i = 0;
	vector<int> solution;
	FOREACH(it, cand) {
	    assert(*it != 0);
	    if(*it > 0) {
		cout << i + 1 << endl;
		FOREACH(it0, solution) {
		    FOREACH(ite, g[*it0]) {
			assert(ite->v != i || (cout << "failed " << *it0 << endl));
		    }
		}
		solution.PB(i);
	    }
	    ++i;
	}
    }

    void comm() {
	VI cand(SIZE(g), 0);

	possible = true;

	REP(i, SIZE(g) / 2) {
	    if(cand[2*i] == 0) {
		Dfs(2*i + 1, cand, i + 1);
	    }

	    if(!possible) {
		possible = true;
		if(cand[2*i] == 0) {
		    Dfs(2*i, cand, i + 1);
		}
	    }

	    if(!possible) {
		break;
	    }
	}

	if(possible) { print(cand); } else { cout << "NIE" << endl;}
    }
};

struct Ve {
    int rev;
};

struct Vv {
    int t;
};


int main(int argc, char *argv[]) {
    int n,m; cin >> n >> m;
    Graph<Vv, Ve> g(2*n);

    REP(i, n) {
	g.EdgeU(2*i, 2*i + 1);
    }

    while(m--) {
	int v0, v1; cin >> v0 >> v1;
	g.EdgeU(v0 - 1, v1 - 1);
    }

    g.comm();
    return 0;
}

