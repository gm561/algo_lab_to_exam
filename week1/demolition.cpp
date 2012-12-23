#include <stdint.h>
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

typedef int64_t num_t;
struct Floor {
    num_t weight;
    num_t capacity;
    num_t cost;

    Floor(num_t w, num_t cap, num_t co) :
	weight(w),
	capacity(cap),
	cost(co) {}
};


int main(int argc, char *argv[]) {

    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    vector<Floor> floors;
    for(int tc = 0 ; tc < TC; ++tc) {
	int n; cin >> n;
	floors.clear();
	floors.reserve(n);
	for(int i = 0; i < n; ++i) {
	    int w, cap, cost; cin >> w >> cap >> cost;
	    floors.push_back(Floor(w, cap, cost));
	}

	num_t min_cost = LONG_MAX;
	num_t lowest_blew_weight = -1;
	for(int i = 0; i < n; ++i) {
	    if(lowest_blew_weight >= floors[i].weight) {
		if(floors[i].capacity < lowest_blew_weight) {
		    lowest_blew_weight = floors[i].capacity;
		}
		lowest_blew_weight -= floors[i].weight;
		continue;
	    }

	    lowest_blew_weight = LONG_MAX;

	    num_t current_cost = 0;
	    num_t current_weight = 0;
	    for(int j = i; j >= 0; --j) {
		if(floors[j].capacity >= current_weight + floors[j].weight) {
		    //blow current floor
		    num_t res_capacity = floors[j].capacity - current_weight - floors[j].weight;
		    lowest_blew_weight = (lowest_blew_weight > res_capacity) ?
			res_capacity : lowest_blew_weight;

		    current_cost += floors[j].cost;
		}
		current_weight += floors[j].weight;
	    }

	    min_cost  = (min_cost > current_cost) ? current_cost : min_cost ;
	}

	cout<<min_cost<<"\n";
    }

    return 0;
}
