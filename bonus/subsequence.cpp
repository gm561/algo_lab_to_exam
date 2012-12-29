#include <iostream>
#include <vector>
#include <stdint.h>

using namespace std;

typedef int64_t num_t;

void algo() {
    num_t n; cin >> n;

    vector<num_t>& numbers =  *(new vector<num_t>());
    vector<num_t>& results = *(new vector<num_t>());

    for (num_t i = 0; i < n; ++i) {
	num_t number; cin >> number;
	numbers.push_back(number);
    }

    results.push_back(numbers[0]);
    num_t max_i = 0;
    num_t max_value = results[0];

    for (num_t i = 1; i < n; ++i) {
    	if(results[i-1] > 0) {
    	    results.push_back(numbers[i] + results[i-1]);
    	}
    	else {
    	    results.push_back(numbers[i]);
    	}

    	if(results[i] > max_value) {
    	    max_value = results[i];
    	    max_i = i;
    	}
    }

    num_t first_i = max_i;
    for(num_t i = max_i; i >= 0; --i) {
    	if(results[i] >= 0) {
    	    first_i = i;
    	}
	else {
	    break;
	}
    }

    cout << max_value << " " << first_i << " " <<  max_i << "\n";

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
