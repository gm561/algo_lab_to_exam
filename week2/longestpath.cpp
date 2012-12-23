#include <queue>
#include <iostream>
#include <vector>

using namespace std;

#define FOR(x, b, e) for(int x=b; x<=(e); ++x)
#define FORD(x, b, e) for(int x=b; x>=(e); ––x)
#define REP(x, n) for(int x=0; x<(n); ++x)
#define VAR(v,n) typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

static const int UNKNOWN = -1;
struct Vertex {
    int number;
    int dfs_value;

    Vertex(int n) : number(n), dfs_value(UNKNOWN) {}
};

typedef vector<vector<Vertex > > Tree;

int DFS(Tree& tree, const Vertex& source, int root) {
    int result = 0;

    for(int i = 0; i < SIZE(tree[source.number]); ++i) {
	if(tree[source.number][i].number != root) {
//	    cout<<"root " << root <<" dfs for vertex: " << tree[source.number][i].number<<endl;
	    if(tree[source.number][i].dfs_value == UNKNOWN) {
		tree[source.number][i].dfs_value =
		    DFS(tree, tree[source.number][i], source.number);
	    }

	    if(result < tree[source.number][i].dfs_value) {
		result = tree[source.number][i].dfs_value;
	    }
	}
    }

//    cout<<"result " << result << endl;

    return result + 1;
}

void algo(Tree& tree) {
    int max_path = 0;
    int max0 = 0;
    int max1 = 0;
    for(int i = 0; i < SIZE(tree); ++i) {
	max0 = 0;
	max1 = 0;
	for(int j = 0; j < SIZE(tree[i]); ++j) {
	    int temp = DFS(tree, tree[i][j], i);
//	    cout<<"vertex " << tree[i][j].number << " value " << temp << endl;
	    if(temp > max1) {
		max0 = max1;
		max1 = temp;
	    }
	    else if(temp > max0) {
		max0 = temp;
	    }
	}

	if(max0 + max1 + 1 > max_path) {
	    max_path = max0 + max1 + 1;
	}
    }

    cout<< max_path <<endl;
}

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    Tree tree;

    for (int tc = 0; tc < TC; ++tc) {
	int n; cin >> n;
	tree.clear();
	tree.resize(n);

	for(int i = 0; i < n - 1; ++i) {
	    int v0,v1; cin >> v0 >> v1;
	    tree[v0].push_back(Vertex(v1));
	    tree[v1].push_back(Vertex(v0));
	}

	algo(tree);
    }

    return 0;
}
