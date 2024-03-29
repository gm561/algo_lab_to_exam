#include <cmath>
#include <queue>
#include <iostream>
#include <vector>
#include <climits>

#define FOR(x, b, e) for(int x=b; x<=(e); ++x)
#define FORD(x, b, e) for(int x=b; x>=(e); ––x)
#define REP(x, n) for(int x=0; x<(n); ++x)
#define VAR(v,n) typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

using namespace std;

//static const int GRID_SIZE = 30;
static const int VELO_COUNT = 7;
static const int VELO_LIM = 4;

typedef vector<vector<vector<vector<int> > > > Graph;
//typedef  vector<vector<vector<int> > > Vertex;

struct Vertex {
    const int x;
    const int y;
    const int vx;
    const int vy;

    Vertex(int x_, int y_, int vx_, int vy_) :
	x(x_),
	y(y_),
	vx(vx_),
	vy(vy_) { }
};

void BFS(Graph& graph,
	 int sx, int sy, int X, int Y, int ex, int ey) {

    queue<Vertex> vStack;
    vStack.push(Vertex(sx,sy,0,0));

    graph[sx][sy][0 + 3][0 + 3] = 1;

    while(!vStack.empty()) {
	Vertex v = vStack.front(); vStack.pop();
//	cout<<"v.x "  << v.x <<" v.y " << v.y << " v.vx " <<v.vx<< " v.vy " <<v.vy<<endl;

	for (int i = 0; i < 3; ++i) {
	    for (int j = 0; j < 3; ++j) {
		if (abs((double)v.vx + i - 1) < VELO_LIM && abs((double)v.vy + j - 1) < VELO_LIM) {

		    int vx = v.vx + i - 1;
		    int vy = v.vy + j - 1;

		    if(v.x + vx >= 0 && v.x + vx < X &&
		       v.y + vy >= 0 && v.y + vy < Y) {

			int x = v.x + vx;
			int y = v.y + vy;

			if(!graph[x][y][vx+3][vy+3]) {
//			    cout<<"x "  << x <<" y " << y << " vx " <<vx<< " vy " <<vy<<endl;

			    vStack.push(Vertex(x, y, vx, vy));
			    graph[x][y][vx+3][vy+3] = graph[v.x][v.y][v.vx+3][v.vy+3] + 1;

			    if(x == ex && y == ey) {
				return;
			    }
			}
			// else {
			//     cout<<"Visited x "  << x <<" y " << y << " vx " <<vx<< " vy " <<vy<< " " << graph[x][y][vx+3][vy+3] <<endl;
			// }
		    }
		}
	    }
	}
    }
}

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    vector<vector<vector<vector<int> > > > graph;

    for(int tc = 0; tc < TC; ++tc) {
	int X,Y; cin >> X >> Y;

	graph.clear();
	graph.resize(X);
	REP(i, X) {
	    graph[i].resize(Y);
	    REP(j, Y) {
		graph[i][j].resize(VELO_COUNT);
		REP(k, VELO_COUNT) {
		    graph[i][j][k].resize(VELO_COUNT);
		}
	    }
	}

	int sx,sy,ex,ey; cin >> sx >> sy >> ex >> ey;

	int count; cin >> count;
	while(count--) {
	    //add obstacles
	    int osx, osy, oex, oey; cin >> osx >> osy >> oex >> oey;
	    for(int k = osx; k <= oex; ++k) {
		for(int l = osy; l <= oey; ++l) {
		    for(int i = 0; i < 7; ++i) {
			for(int j = 0; j < 7; ++j) {
			    graph[k][l][i][j] = -1;
			}
		    }
		}
	    }
	}

	BFS(graph, sx, sy, X, Y, ex, ey);

	int min =  INT_MAX;
	for(int i = 0 ; i < 7; ++i) {
	    for(int j = 0; j < 7; ++j) {
		// cout<<"solution "<<ex<< " " <<ey << " " << i << " " <<j
		//     <<" " << graph[ex][ey][i][j]<<endl;
		if(graph[ex][ey][i][j] != 0 && graph[ex][ey][i][j] < min &&  graph[ex][ey][i][j] > 0) {
		    min = graph[ex][ey][i][j];
		}
	    }
	}

	if(min == INT_MAX) {
	    cout<<"No solution.\n";
	}
	else {
	    cout<<"Optimal solution takes " << min - 1 <<" hops.\n";
	}
    }

    return 0;
}
