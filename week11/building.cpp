
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define ALL(x) x.begin(), x.end()
#define PB(x) push_back(x)

struct Floor {
    int number;

    Floor(int n) : number(n) {}

    bool operator<(const Floor &rhs) const {
	return abs(number) < abs(rhs.number);
    }

    bool operator>(const Floor &rhs) const {
	return abs(number) > abs(rhs.number);
    }
};

void algo() {
    int n; cin >> n;
    if(!n) { cout << 0 << "\n"; return ;}

    vector<Floor> floors; floors.reserve(n);
    for (int i = 0; i < n; ++i) {
	int x;cin >> x;
	floors.PB(Floor(x));
    }

    sort(ALL(floors));

    int s = 1;
    int last = (floors[0].number > 0) ? 1 : -1 ;
    for(int i = 0; i < n; ++i) {
	if(floors[i].number > 0 && last < 0) {
	    last = 1;
	    ++s;
	}
	else if(floors[i].number < 0 && last > 0) {
	    last = -1;
	    ++s;
	}
    }

    cout << s << "\n";
}

int main(int argc, char *argv[]) {
    int tc; cin >> tc;

    while(tc--) algo();

    return 0;
}
