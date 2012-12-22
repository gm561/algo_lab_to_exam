#include <climits>
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

int main(int argc, char *argv[]) {

    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;

    for(int tc = 0; tc < TC; ++tc) {
	int l,m,n; cin >> l >> m >> n;

	int best = INT_MAX;
	int bestM = -1;
	int bestN = -1;

	int nUpper = l/n;
	int mUpper = INT_MAX;

	for(int i = 1; i < l/n; ++i) {
	    if( (i*m / n)*n == i*m ) {
		mUpper = i - 1;
		break;
	    }
	}

	if(nUpper < mUpper) {
	    for(int i = 0; i <= nUpper; ++i) {
		int sol = l - i*n - ((l - i*n)/m)*m;

		if(sol <= best) {
		    best = sol;
		    bestN = i;
		    bestM = ((l-i*n)/m);
		}
	    }
	}
	else {
	    for(int i = 0; i <= mUpper; ++i) {
		int res = ((l - i*m)/n)*n;
		int sol = l - i*m - res;

		if(sol <= best) {
		    best = sol;
		    bestM = i;
		    bestN = res/n;
		}
	    }
	}

	cout << bestM << " " << bestN << " " << best <<"\n";
    }

    return 0;
}
