#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

static const int NONE = -1;

//value = 1 set field, value = -1 unset field
void mark_fields(vector<vector<int> >& board, int value, int i, int j) {
    const int n = board.size();
//    cout<<"Mark fields of beast " << i << " " << j << " with value " << value << endl;

    //mark horizontal fields
    for(int y = 0; y < n; ++y) {
	board[i][y] += value;
    }

    //mark horizontal fields
    for(int x = 0; x < n; ++x) {
	board[x][j] += value;
    }

    //mark first diagonal
    for(int x = max(i - j, 0) ; x < min(n - j + i, n); ++x) {
	assert( x < n && x >= 0);
	assert(x + j - i >= 0 && x + j - i < n);
	board[x][x + j - i] += value;
    }

   // for(int k = 0; k < n; ++k ) {
   //  	for(int j = 0; j < n; ++j ) {
   //  	    cout << board[j][k] <<" ";
   //  	}
   //  	cout<<endl;
   //  }

    //mark second diagonal
    for(int x = max(0, i + j - n + 1) ; x < min(i + j, n); ++x) {
//	cout << -x + j + i << " " << n << endl;
	assert(-x + j + i >= 0 && -x + j + i < n);
	assert(x >= 0 && x < n);

//	cout<<"mark " << x << " " << - x + j + i <<endl;
	board[x][ - x + j + i] += value;
    }

   // for(int k = 0; k < n; ++k ) {
   //  	for(int j = 0; j < n; ++j ) {
   //  	    cout << board[j][k] <<" ";
   //  	}
   //  	cout<<endl;
   //  }

}

void algo(int n) {
    vector<vector<int> > board;
    board.resize(n);
    for (int i = 0; i < n; ++i) {
	board[i].resize(n);
    }

    vector<int> beasts;
    beasts.resize(n);

    for(int i = 0; i < n; ) {
	bool found = false;
	for(int j = max(beasts[i], 0); j < n; ++j) {
	    if(board[i][j] == 0) {
		beasts[i] = j;
		mark_fields(board, 1, i, j);
		found = true;
		break;
	    }
	}

	if(!found) {
	    //backtrack !
	    beasts[i] = NONE;
	    if(i == 0) {
		break;
	    }

	    mark_fields(board, -1, i - 1, beasts[i - 1]);
	    ++beasts[i - 1];
	    i -= 1;
	}
	else {
	    ++i;
	}
    }

    if(beasts[0] == NONE) {
	cout<<"Impossible\n";
    } else {
	for(int i = 0; i < n; ++i) {
	    cout<<beasts[i] << " ";
	}
	cout<<"\n";
    }
}

int main(int argc, char *argv[]) {
    int TC; cin >> TC;
    for (int tc = 0; tc < TC; ++tc) {
	int n; cin >> n;
	algo(n);
    }

    return 0;
}
