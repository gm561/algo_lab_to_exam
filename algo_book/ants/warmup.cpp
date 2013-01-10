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

    void Write() {
	REP(x, SIZE(g)) {
	    cout << x << ":";
	    FOREACH(it, g[x])
		cout << " " << it->v;
	    cout << endl;
	}
    }
};

struct Empty {} ;

int main(int argc, char *argv[]) {
    int n, m, b, e;
    cin >> n >> m;
    Graph<Empty, Empty> graph(n);

    REP(x,m) {
	cin >> b >> e;
	graph.EdgeD(b,e);
    }

    graph.Write();

    return 0;
}
