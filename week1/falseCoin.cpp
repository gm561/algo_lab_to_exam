#include <cassert>
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

int main(int argc, char *argv[])
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    vector<int> coins;
    vector<int> weights;

    for(int tc = 0 ; tc < TC; ++tc) {
	int n, k; cin>>n>>k;
	coins.clear();
	coins.resize(n);

	weights.clear();
	weights.resize(n);

	for(int i = 0; i < k; ++i) {
	    int cn; cin>>cn;

	    for(int j = 0; j < cn; ++j) {
		int ic; cin>>ic;
		weights[ic-1] = -1;
	    }

	    for(int j = 0; j < cn; ++j) {
		int ic; cin>>ic;
		weights[ic-1] = 1;
	    }

	    char sign; cin >>sign;
	    if(sign == '=') {
		for(int i = 0; i < n; ++i) {
		    if(weights[i] != 0) {
			coins[i] = 2;
		    }
		    weights[i] = 0;
		}
	    }
	    else if(sign == '<') {
		for(int i = 0; i < n; ++i) {
		    if(weights[i] == -1) {
			if(coins[i] == 0) {
			    coins[i] = -1;
			}
			else if(coins[i] == 1) {
			    coins[i] = 2;
			}
		    }
		    else if(weights[i] == 1) {
			if(coins[i] == 0) {
			    coins[i] = 1;
			}
			else if(coins[i] == -1) {
			    coins[i] = 2;
			}
		    }
		    else {
			coins[i] = 2;
		    }

		    weights[i] = 0;
		}
	    }
	    else if(sign == '>') {
		for(int i = 0; i < n; ++i) {
		    if(weights[i] == 1) {
			if(coins[i] == 0) {
			    coins[i] = -1;
			}
			else if(coins[i] == 1) {
			    coins[i] = 2;
			}
		    }
		    else if(weights[i] == -1) {
			if(coins[i] == 0) {
			    coins[i] = 1;
			}
			else if(coins[i] == -1) {
			    coins[i] = 2;
			}
		    }
		    else {
			coins[i] = 2;
		    }

		    weights[i] = 0;
		}
	    }
	    else {
		assert(false);
	    }
	}

	int falseCoin = -1;
	for(int i = 0; i < n; ++i) {
	    if(coins[i] != 2) {
		if(falseCoin > -1) {
		    falseCoin = -1;
		    break;
		}
		falseCoin = i;
	    }
	}

	// FOREACH(coin, coins) {
	//     cout<<*coin<<endl;
	// }
	cout<<( (falseCoin != -1) ? falseCoin + 1: 0) << "\n";
    }

    return 0;
}
