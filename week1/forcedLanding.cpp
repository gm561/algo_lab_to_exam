#include <iostream>
#include <vector>

#define FOR(x, b, e) for(int x=b; x<=(e); ++x)
#define FORD(x, b, e) for(int x=b; x>=(e); ––x)
#define REP(x, n) for(int x=0; x<(n); ++x)
#define VAR(v,n) typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

using namespace std;

bool find_tree(const vector<vector<int> >& trees, int x, int y, int s, int r) {
    for(int i = x + 1; i < x + r; ++i) {
	for(int j = y + 1; j < y + s ; ++j) {
//	    cout<<"x : " << i << " y: " << j <<" tree ? " << trees[i][j] <<endl;
	    if(trees[i][j]) {
//		cout<<"Tree found"<<endl;
		return true;
	    }
	}
    }

    return false;
}


int main(int argc, char *argv[])
{
    int TC; cin >> TC;
    vector<vector<int> > trees;
    for(int tc = 0 ; tc < TC; ++tc) {
	//width and height
	int w,h; cin >> w >> h;
	//needed width and runaway
	int s,r; cin >> s >> r;
	//number of trees
	int n; cin >> n;
	trees.clear(); trees.resize(w+1);
	REP(i,w+1) {
	    trees[i].resize(h+1);
	}

	REP(i,n) {
	    int x,y; cin >> x >> y;
	    trees[x][y] = 1;
	}

	int sx = -1, sy = -1;
	//is enough space to land?
	for(int i = 0; i <= w - r; ++i) {
	    for(int j = 0; j <= h - s; ++j) {
		//is tree in landing area?
		if(!find_tree(trees, i, j, s, r)) {
		    sx = i;
		    sy = j;
		    goto solution;
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
