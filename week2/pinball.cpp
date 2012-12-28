#include <iostream>
#include <vector>
#include <stdint.h>
#include <climits>

#define FOR(x, b, e) for(int x=b; x<=(e); ++x)
#define FORD(x, b, e) for(int x=b; x>=(e); ––x)
#define REP(x, n) for(int x=0; x<(n); ++x)
#define VAR(v,n) typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

using namespace std;

typedef int64_t num_t;

num_t sum_points (const vector<num_t>& points, int position, int l) {
    num_t n_points = 0;
    for(int i = 0; i < SIZE(points); ++i) {
	if(i >= position && i < position + l) {
	    n_points += points[position + l];
	}
	else {
	    n_points += points[i];
	}
    }

    return n_points;
}

void algo(const vector<num_t>& points, int n) {
    num_t max_points = LONG_MIN;

    for(int i = 0; i < n; ++i) {
	num_t points_till = 0;
	for(int l = 1; l < n-i-1; ++l) {
	    points_till = sum_points(points, i, l, points_till;
	}
    }
    cout<<max_points<<"\n";
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int TC; cin >> TC;

    vector<num_t> points;

    for(int tc = 0; tc < TC; ++tc) {
	int n; cin >> n;
	points.resize(n);
	for(int i = 0; i < n; ++i) {
	    cin >> points[i];
	}

	algo(points, n);
    }

    return 0;
}
