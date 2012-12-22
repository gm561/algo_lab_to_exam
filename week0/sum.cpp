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
    int TC; cin >> TC;
    for(int tc = 0; tc < TC; ++tc) {
	int n; cin>>n;
	double sum = 0;
	for(int i = 0; i < n; ++i) {
	    double term; cin >> term;
	    sum += term;
	}

	cout<<sum<<"\n";
    }

    return 0;
}
