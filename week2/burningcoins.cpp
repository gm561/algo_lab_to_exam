#include <iostream>
#include <vector>

using namespace std;

inline int play_strategy(int value0, int value1, bool strategy) {
    if(strategy)
	return max(value0, value1);
    else
	return min(value0, value1);
}

//round true maximize
//      false minimize
int f(int i, int j, bool round, const vector<int>& coins, vector<vector<int> >& values) {
 
    if(values[i][j] != -1) {
	return values[i][j];
    }

    if(i == j) {
	return values[i][j] = play_strategy(coins[i], 0, round);
    }

    if(i + 1 == j) {
	return values[i][j] = play_strategy(coins[i], coins[j], round);
    }

    int v0 = f(i + 1, j, !round, coins, values) + ((round) ? coins[i] : 0);
    int v1 = f(i, j - 1, !round, coins, values) + ((round) ? coins[j] : 0);

    return values[i][j] = play_strategy(v0, v1, round);
}

void algo(const vector<int>& coins) {
    if(coins.size() == 0)  {
	cout<< 0 << "\n";
	return;
    }

    int n = coins.size();
    vector<vector<int> > values;
    values.clear();
    values.resize(n);
    for (int i = 0; i < n; ++i) {
	values[i].resize(n,-1);
    }

    cout << f(0, coins.size() - 1, true, coins, values) << "\n";
}


int main(int argc, char *argv[]) {

    int TC; cin >> TC;
    vector<int> coins;
    for(int tc = 0; tc < TC; ++tc) {
	int n; cin >> n;

	coins.clear();
	coins.reserve(n);

	for (int i = 0; i < n; ++i) {
	    int coin; cin >> coin;
	    coins.push_back(coin);
	}

	algo(coins);
    }

    return 0;
}
