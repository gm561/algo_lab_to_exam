#include <vector>
#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

using namespace std;

#define VI vector<int>
#define PB(x) push_back(x)

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

struct Inv {
    int cost;
    int ret;
    int risk;
};

void algo(int n, int m) {

    VI costs(n);
    VI returns(n);
    for (int i = 0; i < n; ++i) {
	cin >> costs[i] >> returns[i];
    }

    vector<VI > covars(n, VI(n));

    for (int i = 0; i < n; ++i) {
	for (int j = 0; j < n; ++j) {
	    cin >> covars[i][j];
	}
    }

    vector<Inv> inv(m);
    for (int i = 0; i < m; ++i) {
	cin >> inv[i].cost >> inv[i].ret >> inv[i].risk;
    }


    for(int j = 0; j < m; ++j) {
	Program qp (CGAL::SMALLER, true, 0, false, 0);

	for(int i = 0; i < n; ++i) {
	    qp.set_a(i, 0, costs[i]);
	    qp.set_a(i, 1,  -returns[i]);
	}

	for(int i = 0; i < n; ++i) {
	    for(int k = 0; k < n; ++k) {
		qp.set_d(i, k,  2*covars[i][k]);
	    }
	}

	qp.set_b(0, inv[j].cost);
	qp.set_b(1, -inv[j].ret);

	Solution s = CGAL::solve_quadratic_program(qp, ET());
	assert (s.solves_quadratic_program(qp));

	if(s.is_optimal() && s.objective_value() <= inv[j].risk) {
	    cout << "Yes.\n";
	}
	else {
	    cout << "No.\n";
	}
    }
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    for(int n,m; cin >> n >> m && n > 0 && m > 0; ) {
	algo(n,m);
    }

    return 0;
}
