#include <climits>
#include <iostream>
#include <vector>
#include <set>

#define FOR(x, b, e) for(int x=b; x<=(e); ++x)
#define FORD(x, b, e) for(int x=b; x>=(e); ––x)
#define REP(x, n) for(int x=0; x<(n); ++x)
#define VAR(v,n) typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

using namespace std;

struct Tree {
    int x;
    int y;
    int i;
    Tree () {}
    Tree (int x_, int y_, int i_) : x(x_), y(y_), i(i_) {}
};

Tree find_tree(const vector<Tree>& trees, int x, int y, int s, int r, int h, const Tree& tree ) {
    for(vector<Tree>::const_iterator t = trees.begin();
	t != trees.end();
	++t) {
	Tree cTree = *t;
	if(cTree.x > x && cTree.x < x + r && cTree.y > y && cTree.y < y + s) {
	    return cTree;
	}
    }

    return Tree(-1,-1, -1);
}


int main(int argc, char *argv[])
{
    int TC; cin >> TC;
    vector<Tree> trees;
    for(int tc = 0 ; tc < TC; ++tc) {
	//width and height
	int w,h; cin >> w >> h;
	//needed width and runaway
	int s,r; cin >> s >> r;
	//number of trees
	int n; cin >> n;
	trees.clear();
	trees.resize(n);
	REP(i,n) {
	    int x,y; cin >> x >> y;
	    trees[i] = Tree(x,y, i);
	}

	int sx = -1, sy = -1;
	//is enough space to land?
	int smallestX = 0;
	for(int i = 0; i <= w - r; i = smallestX) {
	    smallestX = INT_MAX;
	    Tree iTree = trees[0];
	    for(int j = 0; j <= h - s;) {
		//is tree in landing area?
		iTree = find_tree(trees, i, j, s, r, h, iTree);
		if(iTree.x == -1 && iTree.y == -1) {
		    sx = i;
		    sy = j;
		    goto solution;
		} else {
		    if(smallestX > iTree.x) {
			smallestX = iTree.x;
		    }
		    j = iTree.y;
		}
	    }
	}

    solution:
	if(sx != -1 && sy != -1) {
	    cout<< sx << " " <<sy<<"\n";
	}
	else {
	    cout<<"Impossible\n";
	}
    }

    return 0;
}
