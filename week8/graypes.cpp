#include <algorithm>
#include <boost/foreach.hpp>
#include <iostream>

#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;

typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;
typedef Triangulation::Edge_iterator  Edge_iterator;
typedef K::Point_2 Point;

using namespace std;

double ceil_to_double(const K::FT& x)
{
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

int main(int argc, char *argv[]) {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin.sync_with_stdio(false);

    vector<Point> points;
    for( int n; cin >> n && n > 0; ) {
	points.clear(); points.reserve(n);
	for (int i = 0; i < n; ++i) {
	    Point p; cin >> p;
	    points.push_back(p);
	}

	Triangulation t; t.insert(points.begin(), points.end());

	Edge_iterator ei = t.finite_edges_begin();
	K::FT minl = t.segment(*ei).squared_length();

	while(++ei != t.finite_edges_end()) {
	    minl = min(minl, t.segment(*ei).squared_length()) ;
	}

	cout << ceil_to_double(sqrt(minl)  * 50) << "\n";
    }

    return 0;
}
