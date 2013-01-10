#include <iostream>
#include <vector>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

using namespace std;

#define PB(x) push_back(x)
#define VI vector<int>

// choose exact integral type
#ifdef CGAL_USE_GMP
#include <CGAL/Gmpz.h>
typedef CGAL::Gmpz ET;
#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
#endif

typedef CGAL::Quadratic_program<int> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void algo(int n, int m) {
    vector<pair<int, int> > nuts; nuts.reserve(n);
    for (int i = 0; i < n; ++i) {
	int a, b; cin >> a >> b;
	nuts.PB(make_pair(a,b));
    }

    VI costs(m,-1);
    vector<vector<int> > products(m, vector<int>(n, 0));
    for (int i = 0; i < m; ++i) {
	cin >> costs[i];
	for(int j = 0; j < n; ++j) {
	    cin >> products[i][j];
	}
    }

    Program lp (CGAL::SMALLER, true, 0, false, 0);
    for(int i = 0; i < n; ++i) {
	for(int j = 0; j < m; ++j) {
	    lp.set_a(j, i, products[j][i]);
	    lp.set_a(j, i + n, -products[j][i]);
	}
	lp.set_b(i, nuts[i].second);
	lp.set_b(i + n, - nuts[i].first);
    }

    for(int i = 0; i < m; ++i) {
	lp.set_c(i, costs[i]);
    }

    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

    if(s.is_optimal()) {
	cout << floor(CGAL::to_double(s.objective_value())) << "\n";
    }
    else {
	cout << "No such diet.\n";
    }

}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    for(int n,m; cin >> n >> m && n > 0 && m > 0; ) {
	algo(n, m);
    }

    return 0;
}
