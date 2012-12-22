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

static const int MAX_COINS = 10000;

using namespace std;

int foo(int value, const vector<int>& coins, vector<int>& changes) {
//    cout<<changes[value]<<endl;

    if(value < 0) {
	return INT_MAX;
    }

    if(value == 0) {
	return 0;
    }

    if(changes[value]) {
    	return changes[value];
    }

    int min = INT_MAX;
    FOREACH(c, coins) {
	int temp = foo(value - *c, coins, changes);
	if(temp < min) { min = temp ; }
    }

    changes[value] = (min != INT_MAX) ? min + 1 : INT_MAX;

    return changes[value];
}

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    vector<int> coins;
    vector<int> changes;

    for(int tc = 0; tc < TC; ++tc) {
	int c,m; cin >> c >> m;

	coins.clear();
	coins.resize(c);

	for(int i = 0; i < c; ++i) {
	    cin>>coins[i];
	}

	changes.clear();
	changes.resize(MAX_COINS);

	for(int i = 0; i < m; ++i) {
	    int value; cin>>value;

	    if(!changes[value]) {
		foo(value, coins, changes);
	    }

	    if(changes[value] == INT_MAX) {
		cout<<"not possible\n";
	    }
	    else {
		cout<<changes[value]<<"\n";
	    }
	}
    }

    return 0;
}
