#include <iostream>
#include <vector>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

using namespace std;

#define PB(x) push_back(x)
#define VI vector<int>
#define SIZE(x) (int)x.size()

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

inline int calc_norm(VI &as) {
    int value = 0;
    for (int i = 0; i < SIZE(as); ++i) {
	value += as[i]*as[i];
    }

    return sqrt(value);
}

void algo(int n, int d) {
    vector<vector<int> > ineq; ineq.reserve(n);

    vector<int> bs(n);
    for (int i = 0; i < n; ++i) {
	ineq.PB(VI(d));
	for(int j = 0; j < d; ++j) {
	    cin >> ineq[i][j];
	}
	cin >> bs[i];
    }

    Program lp (CGAL::SMALLER, false, 0, false, 0);

    lp.set_l(d + 1, true, 0);
    for (int i = 0; i < n; ++i) {
	for (int j = 0; j < d; ++j) {
	    lp.set_a(j, i, ineq[i][j]);
	    lp.set_a(j, i + n, ineq[i][j]);
	}

	int norm = calc_norm(ineq[i]);
//	cout << "norm " << norm << endl;
	lp.set_a(d + 1, i + n, norm);
	lp.set_b(i, bs[i]);
	lp.set_b(i + n,  bs[i]);
    }

    lp.set_c(d + 1, -1);

    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

//    cout << s;
    if(s.is_optimal()) {
	cout << -1 * ceil(CGAL::to_double(s.objective_value())) << "\n";
    }
    else if(s.is_unbounded()){
	cout << "inf\n";
    }
    else if(s.is_infeasible()) {
	cout << "none\n";
    }

}


int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    for(int n,d; cin >> n >> d && n > 0 && d > 0; ) {
	algo(n, d);
    }

    return 0;
}
