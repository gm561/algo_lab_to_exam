#include <iostream>
#include <vector>
#include <cassert>

#include <CGAL/basic.h>
#include <CGAL/QP_models.h>
#include <CGAL/QP_functions.h>

#define PB(x) push_back(x)
#define VI vector<int>

const int INF = 1000000001;

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

using namespace std;

struct Cell {
    int x,y,z;
    Cell(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
};


// int add_degree(int var,
// 	       Program &lp,
// 	       const vector<Cell>& cells,
// 	       int degree) {

//     int factor = 1;
//     for(int inum = 0; inum < SIZE(cells); ++inum)
// 	if(factor > 0 && inum >= h) factor = -1;

// 	for(int i = 0; i <= degree; ++i) {
// 	    for(int j = 0; j <= degree - i; ++j) {
// 		int l = degree - i - j; assert(l + i + j == d);
// 		double result = pow(cells[inum].x, i) *
// 		    pow(cell[inum].y, j) *
// 		    pow(cells[inum].z, l);

// 		lp.set_a(var, inum, factor*result);
// 		++var;
// 	    }
// 	}

//     return var;
// }

void algo() {
    int h,t; cin >> h >> t;

    vector<Cell> cells; cells.reserve(h + t);

    for (int i = 0; i < h + t; ++i) {
	int x,y,z; cin >> x >> y >> z;
	cells.PB(Cell(x,y,z));
    }

    const int gamma = 0;
    bool sol = false;
    int var = gamma + 1;

    Program lp (CGAL::SMALLER, false, 0, false, 0);
    lp.set_u(gamma, true, 1);
    lp.set_c(gamma, -1);

    for(int i = 0; i < h + t; ++i) {
	lp.set_a(gamma, i, 1);
    }

    int degree = -1;
    while(degree < 9 && !sol) {
    	++degree;
    	int varI = var;
    	for(int he = 0; he < max(h,t); ++he) {
    	    var = varI;
    	    for(int i = 0; i <= degree; ++i) {
    		for(int j = 0; j <= degree - i; ++j) {
    		    int l = degree - i - j; assert(l + i + j == degree);
    		    if(he < h) {
    			double result =
    			    pow(cells[he].x, i) * pow(cells[he].y, j)*
    			    pow(cells[he].z, l);

    			lp.set_a(var, he, result);
    		    }
    		    if(he < t) {
    			double result =
    			    pow(cells[he + h].x, i) * pow(cells[he + h].y, j)*
    			    pow(cells[he + h].z, l);

    			lp.set_a(var, he + h,  -result);
    		    }
    		    ++var;
    		}
    	    }
    	}
    	varI = var;

    	CGAL::Quadratic_program_options options;
    	options.set_pricing_strategy(CGAL::QP_BLAND);

    	Solution s = CGAL::solve_linear_program(lp, ET(), options);
    	assert (s.solves_linear_program(lp));

    	if(s.is_optimal() && s.objective_value() < 0) {
    	    sol = true;
    	}
    }

    if(!sol) {
	int min_degree = degree = 10;
	int max_degree = 30;

	while(min_degree <= max_degree) {
	    int d = (min_degree + max_degree) / 2;

	    Program lp (CGAL::SMALLER, false, 0, false, 0);
	    lp.set_u(gamma, true, 1);
	    lp.set_c(gamma, -1);

	    for(int i = 0; i < h + t; ++i) {
		lp.set_a(gamma, i, 1);
	    }

	    int varI = var;
	    for(int he = 0; he < max(h,t); ++he) {
		var = 1;
		for(int k = 0; k <= d; ++k) {
		    for(int i = 0; i <= k; ++i) {
			for(int j = 0; j <= k - i; ++j) {
			    int l = k - i - j; assert(l + i + j == k);
			    if(he < h) {
				double result = pow(cells[he].x, i) * pow(cells[he].y, j)*
				    pow(cells[he].z, l);

				lp.set_a(var, he, result);
			    }
			    if(he < t) {
				double result = pow(cells[he + h].x, i) *
				    pow(cells[he + h].y, j)* pow(cells[he + h].z, l);

				lp.set_a(var, he + h, -result);
			    }
			    ++var;
			}
		    }
		}
	    }
//	varI = var;

	    CGAL::Quadratic_program_options options;
	    options.set_pricing_strategy(CGAL::QP_BLAND);

	    Solution s = CGAL::solve_linear_program(lp, ET(), options);
	    assert (s.solves_linear_program(lp));

//	    cout << "Min degree " << min_degree << endl ;
//	cout << "Current degree " << d << " Min degree " << min_degree << endl;
	    if(s.is_optimal() && s.objective_value() < 0) {
		sol = true;
		max_degree = d - 1;
		degree = d;
	    }
	    else {
		min_degree = d + 1;
	    }
	}
    }

    if(!sol) {
	cout << "Impossible!\n";
    } else {
	cout << degree << "\n";
    }
}


int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int tc; cin >> tc;
    while(tc--) {
	algo();
    }

    return 0;
}
