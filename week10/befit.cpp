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

typedef CGAL::Quadratic_program<double> Program;
typedef CGAL::Quadratic_program_solution<ET> Solution;

void algo(int n) {
    int d; cin >> d;

    Program lp (CGAL::SMALLER, false, 0, false, 0);

    for (int i = 0; i < n; ++i) {
	double t; cin >> t;
	double f; cin >> f;

	for(int j = 0; j < d + 1; ++j) {
	    lp.set_a(j, i, pow(t, j));
	    lp.set_a(j, i + n, -pow(t, j));
	}

	lp.set_a(d + 1, i, -1);
	lp.set_b(i, f);

	lp.set_a(d + 1, i + n , -1);
	lp.set_b(i + n, -f);
    }

    lp.set_c(d + 1, 1);

    Solution s = CGAL::solve_linear_program(lp, ET());
    assert (s.solves_linear_program(lp));

    cout << ceil(CGAL::to_double(s.objective_value())) << "\n";
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    for(int n; cin >> n && n > 0; ) {
	algo(n);
    }

    return 0;
}
