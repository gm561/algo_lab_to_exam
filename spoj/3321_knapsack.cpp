#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

typedef int64_t num_t;

struct Item {
    num_t size;
    num_t value;

    Item(num_t size_, num_t value_) :  size(size_) , value(value_) {}
};

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int S, N; cin >> S >> N;
    vector<Item> items; items.reserve(N);
    for(int i = 0; i < N; ++i) {
	num_t size, value; cin >> size >> value;
	items.push_back(Item(size, value));
    }

    vector<vector<int> > solutions;
    solutions.resize(S + 1);
    for (int i = 0; i <= S; ++i) {
	solutions[i].resize(N);
    }

    for(int i = 0; i <= S; ++i) {
	solutions[i][0] = (i >= items[0].size) ? items[0].value : 0;
    }

    for(int i = 1; i <= S; ++i) {
	for(int j = 1; j < N; ++j) {
	    num_t s0 = solutions[i][j-1];

	    num_t s1 =
		(i - items[j].size >= 0) ?
		solutions[i - items[j].size][j-1] + items[j].value : 0;

	    solutions[i][j] = max(s0,s1);
	}
    }

    cout<<solutions[S][N-1] << "\n";

    return 0;
}
