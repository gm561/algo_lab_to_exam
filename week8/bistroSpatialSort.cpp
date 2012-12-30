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

double ceil_to_double(const K::FT& x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

struct IPoint : public K::Point_2{
    IPoint(K::FT& x, K::FT& y, size_t i) : K::Point_2(x,y), index(i) {
    }

    size_t index;
};

int main(int argc, char *argv[]) {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin.sync_with_stdio(false);

    vector<Point> restaurants;
    vector<IPoint> locations;
    for(int n; cin >> n && n > 0;) {
	restaurants.clear(); restaurants.reserve(n);
	for (int i = 0; i < n; ++i) {
	    Point p; cin >> p;
	    restaurants.push_back(p);
	}

	int m; cin >> m;
	locations.clear();locations.reserve(m);
	for (int i = 0; i < m; ++i) {
	    double x,y; cin >> x >> y;
	    IPoint p(x, y, i);
	    locations.push_back(p);
	}

	Triangulation t;
	t.insert(restaurants.begin(), restaurants.end());

	CGAL::spatial_sort(locations.begin(), locations.end());

	vector<K::FT> results(locations.size());
	Triangulation::Face_handle fh = t.infinite_face();
	BOOST_FOREACH(IPoint p, locations) {
	    Triangulation::Vertex_handle vh = t.nearest_vertex(p, fh);
	    results[p.index] = CGAL::squared_distance(p, vh->point());
	    fh = vh->face();
	}

	BOOST_FOREACH(K::FT number, results) {
	    cout << number << "\n";
	}
    }


    return 0;
}
