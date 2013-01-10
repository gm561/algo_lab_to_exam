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

// round down to next int (the result will be small enough)
int ceil_to_int(const CGAL::Quotient<ET>& x) {
  int a = std::ceil(CGAL::to_double(x));
  while (a < x) a += 1;
  while (a-1 >= x) a -= 1;
  return a;
}



inline void f1(int a, int b) {
    Program qp (CGAL::SMALLER, true, 0, false, 0);

    const int X = 0;
    const int Y = 1;

    // x + y <= 4
    qp.set_a(X, 0, 1); qp.set_a(Y, 0, 1); qp.set_b(0, 4);
    // -x + 2y <= ab
    qp.set_a(X, 1, -1); qp.set_a(Y, 1, 2); qp.set_b(1, a*b);
    // -x + y <= 1
    qp.set_a(X, 2, -1); qp.set_a(Y, 2, 1); qp.set_b(2,1);
    //max by - a*x^2 => min -by + a*x^2
    qp.set_c(Y, -b);
    qp.set_d(X, X, 2*a);

    Solution s = CGAL::solve_quadratic_program(qp, ET());
    assert (s.solves_quadratic_program(qp));

    if(s.is_optimal()) {
	cout << -1*ceil_to_int(s.objective_value()) << "\n";
    }
    else if(s.is_infeasible()) {
	cout << "no\n";
    }
    else if(s.is_unbounded()) {
	cout << "unbounded\n";
    }
}


inline void f2(int a, int b) {
    Program qp (CGAL::SMALLER, false, 0, false, 0);

    const int X = 0;
    const int Y = 1;
    const int Z = 2;

    qp.set_u(X, true, 0);
    qp.set_u(Y, true, 0);

    // x + y >= -4 -> -x - y <= 4
    qp.set_a(X, 0, -1); qp.set_a(Y, 0, -1); qp.set_b(0, 4);
    // 4x + 2y  + z^2 >= -ab -> -4x - 2y - z^2 <= ab
    qp.set_a(X, 1, -4); qp.set_a(Y, 1, -2); qp.set_a(Z, 1, -1); qp.set_b(1, a*b);
    // -x + y >= -1 -> x - y <= 1
    qp.set_a(X, 2, 1); qp.set_a(Y, 2, -1); qp.set_b(2, 1);
    //min a*x^2  + by + z^4
    qp.set_c(Y, b);
    qp.set_d(X, X, 2*a);
    qp.set_d(Z, Z, 2);

    Solution s = CGAL::solve_quadratic_program(qp, ET());
    assert (s.solves_quadratic_program(qp));

    if(s.is_optimal()) {
	cout << ceil_to_int(s.objective_value()) << "\n";
    }
    else if(s.is_infeasible()) {
	cout << "no\n";
    }
    else if(s.is_unbounded()) {
	cout << "unbounded\n";
    }
    else {
	throw int();
    }
}


void algo() {
    for(int p; cin >> p && p > 0; ) {
	int a,b; cin >> a >> b;
	(p == 1) ? f1(a, b) : f2(a, b);
    }
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    algo();

    return 0;
}
