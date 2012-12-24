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

bool is_solution(int row, int column,
		 const vector<vector<int> > &board) {

    int n = SIZE(board);

    assert(column < n);

    //for all x; y = c;
    for(int i = 0; i < n; ++i) {
	if(board[i][column]) {
	    return false;
	}
    }

    // y = x + c - r
    for(int i = max(0, -column + row); i < min(n, n - column + row); ++i) {
	assert(i >= 0 && i < n);
	assert(i + column - row >= 0 && i + column - row < n);

	if(board[i][i + column - row]) {
	    return false;
	}
    }

    //y = -x + c + r
    for(int i = max(0, column + row - n + 1); i < min(n, column + row + 1); ++i) {
	assert(i >= 0 && i < n);
	assert(-i + column + row >= 0 && -i + column + row < n);
	if(board[i][-i + column + row]) {
	    return false;
	}
    }

    return true;
}

inline void mark_fields(int row, int column,
		 vector<vector<int> >& board,
		 int result) {

    int n = SIZE(board);

    assert(column < n);

    //for all x; y = c;
    for(int i = 0; i < n; ++i) {
	board[i][column] += result;
    }

    // //for all x; y = c;
    // for(int i = 0; i < n; ++i) {
    // 	board[row][i] += result;
    // }

    // y = x + c - r
    for(int i = max(0, -column + row); i < min(n, n - column + row); ++i) {
	assert(i >= 0 && i < n);
	assert(i + column - row >= 0 && i + column - row < n);

	board[i][i + column - row] += result;
    }

    //y = -x + c + r
    for(int i = max(0, column + row - n + 1); i < min(n, column + row + 1); ++i) {
	assert(i >= 0 && i < n);
	assert(-i + column + row >= 0 && -i + column + row < n);

//	cout<<"mark " << i << " " << -i + column + row <<endl;
	board[i][-i + column + row] += result;
    }

    // REP(i, n) {
    // 	REP(j, n) {
    // 	    cout<< board[j][i] << " ";
    // 	}
    // 	cout<< endl;
    // }
}

bool backtrack(int row, vector<int>& solutions,
	       vector<vector<int> >& board) {

    if(row == SIZE(board)) {
	return true;
    }

    //iterate possible solutions
    bool result = false;
    for(int i = 0; i < SIZE(board) && !result; ++i) {
//	cout << "Try position " << row << " " << i << endl;
	if(!board[row][i]) {
	    mark_fields(row, i, board, 1);
	    result = backtrack(row + 1, solutions, board);

	    if(result) {
		solutions[row] = i;
	    }
	    else {
		mark_fields(row, i, board, -1);
	    }
	}
    }

    return result;
}

void algo(int n) {
    vector<int> solution;
    solution.resize(n);

    vector<vector<int> > board;
    board.resize(n);
    REP(i,n) {
	board[i].resize(n);
    }

    bool result = backtrack(0, solution, board);

    if(result) {
	REP(i, SIZE(board)) {
	    cout<< solution[i] + 1<< " ";
	}
	cout << "\n";
    }
    else {
	cout<< "Impossible\n";
    }
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
