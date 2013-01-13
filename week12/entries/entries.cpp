#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

#include <boost/foreach.hpp>

#include <boost/graph/connected_components.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>

using namespace boost;
using namespace std;

typedef adjacency_list <vecS, vecS, undirectedS,
			 no_property, property < edge_weight_t, int > > Graph;

typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;

using namespace std;

typedef vector<int> VI;
typedef long long LL;

#define FOR(x, b, e) for(int x = b; x <= (e); ++x)
#define FORD(x, b, e) for(int x = b; x >= (e); --x)
#define REP(x, n) for(int x = 0; x < (n); ++x)
#define VAR(v, n) __typeof(n) v = (n)
#define ALL(c) (c).begin(), (c).end()
#define SIZE(x) ((int)(x).size())
#define FOREACH(i, c) for(VAR(i, (c).begin()); i != (c).end(); ++i)
#define PB push_back
#define ST first
#define ND second
#define MP make_pair

typedef pair<int,int> PII;
typedef vector<PII> VPII;

template<class V, class E> struct MGraph {
    struct Ed : E {
	int v;
	Ed(E p, int w) : E(p), v(w) {}
    };

    struct Ve : V,vector<Ed> {};

    vector<Ve> g;
    MGraph(int n=0) : g(n) {}

    void EdgeU(int b, int e, E d = E()) {
	Ed eg(d,e); eg.rev=SIZE(g[e])+(b==e); g[b].PB(eg);
	eg.rev=SIZE(g[eg.v=b])-1; g[e].PB(eg);
    }

    int id,l;

    //store visit time
    int t;
    //list of bridges
    VPII *br;

    //search graph in DFS like way
    int BriArtR(int v, int p) {
	int l = g[v].d = ++t;
	FOREACH(it, g[v]) if (it->v != p)
	    l = min(l, !g[it->v].d ? BriArtR(it->v, v) : g[it->v].d);

	if(g[p].d<=l) g[p].art = 1;
	if(g[p].d<l) br->PB(MP(min(v, p), max(v, p)));

	return l;
    }

    void BriArt(VPII &res) {
	res.clear(); br = &res;
	t = 0;
	REP(x, SIZE(g)) g[x].art = g[x].d = 0;

	REP(x, SIZE(g)) if(!g[x].d) {
	    g[x].d=++t;
	    int c = 0;
	    FOREACH(it, g[x]) if (!g[it->v].d) {c++; BriArtR(it->v, x);}
	    g[x].art = (c>1);
	}
    }
};

struct VsBriArt {
    int d;
    bool art;
};
struct VeBriArt {
    int rev;
};

//delete entries
void algo0(VPII &edges, int n) {
	Graph graph(n);
	property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, graph);
	int u,v;
	FOREACH(e, edges) {
	    u = e->first; v = e->second;
	    Edge edge; bool inserted;
	    tie(edge, inserted) = add_edge(u, v, graph);
	    weightmap[edge] = 1;
	}

	if(num_vertices(graph) < 3) {
	    cout << "no\n"; return;
	}

	std::vector<int> component(num_vertices(graph));
	int num = connected_components(graph, &component[0]);
	if(num > 1) {
	    cout << "no\n"; return;
	}

	std::vector<Edge> spanning_tree; spanning_tree.reserve(n-1);
	kruskal_minimum_spanning_tree(graph, std::back_inserter(spanning_tree));

	vector<int> colors(n, 0);
	vector<vector<int> > ngraph(n);

	BOOST_FOREACH(Edge e, spanning_tree) {
	    int v0 = source(e, graph);
	    int v1 = target(e, graph);

	    ngraph[v0].push_back(v1);
	    ngraph[v1].push_back(v0);
	}

	queue<int> vqueue;
	vqueue.push(0);
	colors[0] = 1;
	while(!vqueue.empty()) {
	    int v = vqueue.front(); vqueue.pop();
	    BOOST_FOREACH(int vn, ngraph[v]) {
		if(colors[vn] == 0) {
		    colors[vn] = colors[v] % 2 + 1;
		    vqueue.push(vn);
		}
	    }
	}

	int color1 = 0;
	int color2 = 0;

	for(int i = 0; i < n; ++i) {
	    if(colors[i] == 1) {
		++color1;
		if(color1 > 1) {
		    colors[i] = 3;
		    break;
		}
	    }
	    else if(colors[i] == 2){
		++color2;
		if(color2 > 1) {
		    colors[i] = 3;
		    break;
		}
	    }
	    else {
//		throw int();
	    }
	}

	vector<int> colors1; colors.reserve(n);
	vector<int> colors2; colors.reserve(n);
	vector<int> colors3; colors.reserve(n);

	for(int i = 0; i < n; ++i) {
	    int c = colors[i];
	    if(c == 1) {
		colors1.push_back(i);
	    }
	    else if(c == 2) {
		colors2.push_back(i);
	    }
	    else if(c == 3) {
		colors3.push_back(i);
	    }
	    else {
		assert(false);
	    }
	}

// 	if(colors1.empty () || colors2.empty() || colors3.empty()) {
// //	    throw int();
// 	}

	cout << "yes\n";
	cout << colors1.size() <<" ";
	BOOST_FOREACH(int v, colors1) {
	    cout << v << " ";
	}
	cout<< "\n" << colors2.size() << " ";
	BOOST_FOREACH(int v, colors2) {
	    cout << v << " ";
	}
	cout<<"\n" << colors3.size() << " ";
	BOOST_FOREACH(int v, colors3) {
	    cout<< v << " ";
	}
	cout << "\n";

}


void algo() {
    int n, m; cin >> n >> m;
    MGraph<VsBriArt, VeBriArt> g(n);
    VPII edges; edges.reserve(m);
    while(m--) {
	int u,v; cin >> u >> v;
	g.EdgeU(u, v);
	edges.PB(MP(u,v));
    }

    VPII res;
    g.BriArt(res);

    bool possible = true;
    for (int i = 0; i < n && possible; ++i)
	possible = !g.g[i].art;


    if(possible) {
	algo0(edges, n);
    }
    else {
	cout << "no\n";
    }
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int tc; cin >> tc;
    while(tc--)
	algo();

    return 0;
}
