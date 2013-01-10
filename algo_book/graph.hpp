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
	    FOREACH(it, g[x]) cout << " " << it->v;
	    cout << endl;
	}
    }
};

