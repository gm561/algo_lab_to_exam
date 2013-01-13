#include <iostream>

#include <iostream>
#include <cassert>
#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

using namespace std;

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

#define VI vector<int>
#define PB(x) push_back(x)

const int INF = 1000000001;

struct Inv {
    int cost;
    int ret;
    int risk;
};


// round down to next int (the result will be small enough)
int ceil_to_int(const CGAL::Quotient<ET>& x) {
  int a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}

void algo(int n, int m) {
    VI costs(n), returns(n);
    for (int i = 0; i < n; ++i)
	cin >> costs[i] >> returns[i];

    vector<VI > covars(n, VI(n));

    for (int i = 0; i < n; ++i)
	for (int j = 0; j < n; ++j)
	    cin >> covars[i][j];

    vector<Inv> inv(m);
    for (int i = 0; i < m; ++i)
	cin >> inv[i].cost >> inv[i].risk;

    for(int j = 0; j < m; ++j) {
	int max = 10000000; int min = 0; int opt = 0;
	Program qp (CGAL::SMALLER, true, 0, false, 0);

	while(min <= max) {
	    double ret = (min + max) / 2;

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
	    qp.set_b(1, -ret);

	    Solution s = CGAL::solve_quadratic_program(qp, ET());
	    assert (s.solves_quadratic_program(qp));

	    if(s.is_optimal() && s.objective_value() <= inv[j].risk) {
		min = ret + 1;
		opt = ret;
	    }
	    else {
		max = ret - 1;
	    }
	}

	cout << ceil_to_int(opt) << "\n";
    }
}

int main(int argc, char *argv[]) {
    for(int n,m; cin >> n >> m && n > 0 && m > 0; )
	algo(n,m);


    return 0;
}

