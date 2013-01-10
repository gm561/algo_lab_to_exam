#include <cmath>
#include <climits>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Point {
    int r,c;
    Point(int r_, int c_) : r(r_), c(c_) {}
};

void update(const vector<vector<int> > &node,
	    vector<vector<int> > &steeps,
	    queue<Point> &points_queue,
	    int row, int column, int rm, int cm) {
    int steep = max(node[row + rm][column + cm] - node[row][column], steeps[row][column]);

    if(steeps[row + rm][column + cm] > steep) {
	steeps[row + rm][column + cm] = steep;
	points_queue.push(Point(row + rm, column + cm));
    }
}

void algo() {
    int n; cin >> n;
    int h; cin >> h;
    int s; cin >> s;

    vector<vector<int> > nodes(n, vector<int>(n));
    for(int i = 0; i < n; i++) {
	for(int j = 0; j < n; ++j) {
	    cin >> nodes[i][j];
	}
    }

    vector<Point> houses; houses.reserve(h);
    for (int i = 0; i < h; ++i) {
	int x,y; cin >> x >> y;
	houses.push_back(Point(x,y));
    }

    vector<Point> shops; shops.reserve(s);
    for (int i = 0; i < s; ++i) {
	int x,y; cin >> x >> y;
	shops.push_back(Point(x,y));
    }

    vector<vector<int> > steeps(n, vector<int>(n, INT_MAX));
    queue<Point> points_queue;
    for(int i = 0; i < s; ++i) {
	Point s = shops[i];
	points_queue.push(s);
	steeps[s.r][s.c] = 0;
	while(!points_queue.empty()) {
	    Point p = points_queue.front(); points_queue.pop();
	    int row = p.r;
	    int column = p.c;

//	    cout << "points " << p.r << " " << p.c << endl;
	    for(int i = -1; i <= 1; ++i) {
		for(int j = -1; j <= 1; ++j) {
		    if(abs((double)i) != abs((double)j) && row + i >= 0 && row + i < n &&
		       column + j >= 0 && column + j < n) {
			update(nodes, steeps, points_queue, row, column, i , j);
		    }
		}
	    }
	}
    }

    // for(int i = 0; i < 5; ++i) {
    // 	for(int j = 0; j < 5; ++j) {
    // 	    cout << steeps[i][j] << " ";
    // 	}
    // 	cout << endl;
    // }

    // cout << endl;
    // cout << endl;

    int max_steep = 0;
    for(int i = 0; i < h; ++i) {
	Point house = houses[i];
//	cout << house.r << " " << house.c << endl;
	int steep = steeps[house.r][house.c];
//	cout << steep << endl;
	max_steep = max(max_steep, steep);
    }

    cout << max_steep << endl;
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    for(int tc = 0; tc < TC; ++tc) {
	algo();
    }

    return 0;
}
