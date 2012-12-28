#include <unistd.h>
#include <ctime>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <vector>
#include <climits>

#define FOR(x, b, e) for(int x=b; x<=(e); ++x)
#define FORD(x, b, e) for(int x=b; x>=(e); ––x)
#define REP(x, n) for(int x=0; x<(n); ++x)
#define VAR(v,n) typeof(n) v=(n)
#define ALL(c) c.begin(),c.end()
#define SIZE(x) (int)x.size()
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

using namespace std;


inline void mark_fields(int row, int column,
		 vector<vector<int> >& board,
		 int result) {

    int n = SIZE(board);

    assert(column < n);

    //for all x; y = c;
    for(int i = 0; i < n; ++i) {
	if(i != row)
	    board[i][column] += result;
    }

    // y = x + c - r
    for(int i = max(0, -column + row); i < min(n, n - column + row); ++i) {
	assert(i >= 0 && i < n);
	assert(i + column - row >= 0 && i + column - row < n);

	if(i != row)
	    board[i][i + column - row] += result;
    }

    //y = -x + c + r
    for(int i = max(0, column + row - n + 1); i < min(n, column + row + 1); ++i) {
	assert(i >= 0 && i < n);
	assert(-i + column + row >= 0 && -i + column + row < n);

//	cout<<"mark " << i << " " << -i + column + row <<endl;
	if(i != row)
	    board[i][-i + column + row] += result;
    }

    // REP(i, n) {
    // 	REP(j, n) {
    // 	    cout<< board[j][i] << " ";
    // 	}
    // 	cout<< endl;
    // }
}


inline bool is_solution(int row, int column,
		 const vector<vector<int> > &board) {

    return !board[row][column];
}


void algo(int n) {
    vector<int> solution;
    solution.resize(n);

    vector<vector<int> > board;
    board.resize(n);
    REP(i,n) {
	board[i].resize(n);
    }

    //randomize initial solution
    REP(i, SIZE(board)) {
	solution[i] = rand() % SIZE(board);
	mark_fields(i, solution[i], board, 1);
    }

    if(n == 1) {
	cout << 1 <<"\n";
	return;
    }

    if(n < 4) {
	cout<<"Impossible\n";
	return;
    }

    int max_conflicts = 1;
    int index = 0;
    int last_index = -1;
    while(max_conflicts) {
	max_conflicts = 0;
	index = -1;

	REP(i, SIZE(board)) {
	    if(board[i][solution[i]] > max_conflicts && last_index != i) {
		max_conflicts = board[i][solution[i]];
		index = i;
	    }
	}

	last_index = index;
	if(max_conflicts == 0) {
	    break;
	}

	int min_conflicts = INT_MAX;
	int min_column = 0;

	int k = rand() % 10*n;
	if( k <= 6*n) {
	    for(int i = 0; i < n; ++i) {
		if(board[index][i] < min_conflicts && i != solution[index]) {
		    min_conflicts = board[index][i];
		    min_column = i;
		}
	    }
	}
	else {
	    min_column = rand() % n;
	}

	mark_fields(index, solution[index], board, -1);
	solution[index] = min_column;
	mark_fields(index, solution[index], board, 1);

	// REP(i, n) {
	//     REP(j, n) {
	// 	cout<< board[j][i] << " ";
	//     }
	//     cout<< endl;
	// }
	// cout<<endl;

	// REP(i, n) {
	//     REP(j, n) {
	// 	if(solution[j] == i) {
	// 	    cout << "o ";
	// 	}
	// 	else {
	// 	    cout <<"x ";
	// 	}
	//     }
	//     cout<< endl;
	// }
	// cout<< endl;

	// usleep(1000000);
    }

    REP(i, SIZE(board)) {
	assert(is_solution(i, solution[i], board));
	cout<< solution[i] + 1<< " ";
    }
    cout << "\n";

    // if(result) {
    // 	REP(i, SIZE(board)) {
    // 	    cout<< solution[i] + 1<< " ";
    // 	}
    // 	cout << "\n";
    // }
    // else {
    // 	cout<< "Impossible\n";
    // }
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    int TC; cin >> TC;

    for(int tc = 0 ; tc < TC; ++tc) {
	int n; cin >> n;
	algo(n);
    }

    return 0;
}
