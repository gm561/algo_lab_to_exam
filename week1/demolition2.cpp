#include <stdint.h>
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

typedef int64_t num_t;

struct Floor {
    num_t weight;
    num_t capacity;
    num_t cost;
    num_t weight_under;
    num_t number;

    Floor(num_t w, num_t cap, num_t co, num_t number_) :
	weight(w),
	capacity(cap),
	cost(co),
<<<<<<< HEAD
	weight_under(weight_under_) { }
=======
	weight_under(0),
	number(number_){}
>>>>>>> demolition_fixed

    bool operator<(const Floor& floor) const {
	if(weight_under + capacity != floor.weight_under + floor.capacity )
	    return weight_under + capacity < floor.weight_under + floor.capacity;
	else
	    return number < floor.number;
    }
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
	    floors.push_back(Floor(w, cap, cost, i));
	}

	num_t min_cost = floors[0].cost;
	num_t current_cost = floors[0].cost;
	num_t total_weight = floors[0].weight;

	vector<Floor> not_blew;
	not_blew.push_back(floors[0]);

	for(int i = 1; i < n; ++i) {
            floors[i].weight_under = total_weight;
	    total_weight += floors[i].weight;

<<<<<<< HEAD
	    for(vector<Floor>::iterator it = not_blew.begin();
		it != not_blew.end(); ) {
		Floor floor = *it;
		if( floor.capacity + floor.weight_under - total_weight < 0 ) {
		    not_blew.erase(it);
		    it = not_blew.begin();
		    current_cost -= floor.cost;
		}
		else {
		    ++it;
=======
	    while(!stop && !not_blew.empty()) {
		set<Floor>::const_iterator cit = not_blew.begin();
		Floor floor = *cit;
		if(floor.capacity + floor.weight_under - total_weight >= 0) {
		    stop = true;
		}
		else {
		    current_cost -= floor.cost;
		    not_blew.erase(cit);
>>>>>>> demolition_fixed
		}
	    }

	    current_cost += floors[i].cost;
	    not_blew.push_back(floors[i]);

	    min_cost = (min_cost > current_cost) ? current_cost : min_cost;
	}

	cout<<min_cost<<"\n";
    }

    return 0;
}

