#include <algorithm>
#include <boost/foreach.hpp>
#include <iostream>

#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Triangulation_vertex_base_with_info_2<K::FT,K> Vb;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;

typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;

typedef K::Point_2 Point;
typedef K::Iso_rectangle_2 Rectangle;

using namespace std;

double ceil_to_double(const K::FT& x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

double hours(const K::FT& x) {
    return ceil(sqrt(sqrt(x) - 0.5));
}

void algo(int n) {
    int l,b,r,t; cin >> l >> b >> r >> t;

    vector<Point> points; points.reserve(n);
    for(int i = 0; i < n; ++i) {
	Point p; cin >> p;
	points.push_back(p);
    }

    Triangulation dt;
    dt.insert(points.begin(), points.end());

    //calculate distances to dish
    for(Triangulation::Finite_vertices_iterator vi = dt.finite_vertices_begin();
	vi != dt.finite_vertices_end();
	++vi) {

	vi->info() = min ( min(vi->point().x() - l, r - vi->point().x()),
			   min(vi->point().y() - b, t - vi->point().y()));

	vi->info() *= vi->info();
    }

    //calculate distnaces between verticies
    for(Edge_iterator ei = dt.finite_edges_begin();
	ei != dt.finite_edges_end(); ++ei) {
	Triangulation::Vertex_handle vh0 = ei->first->vertex((ei->second + 1) % 3);
	Triangulation::Vertex_handle vh1 = ei->first->vertex((ei->second + 2) % 3);

	K::FT d = CGAL::squared_distance(vh0->point(), vh1->point()) / 4;
	vh0->info() = min(d, vh0->info());
	vh1->info() = min(d, vh1->info());
    }


    vector<K::FT> death_times; death_times.reserve(n);
    for(Vertex_iterator vi = dt.finite_vertices_begin();
	vi != dt.finite_vertices_end(); ++vi) {
	death_times.push_back(vi->info());
    }

    sort(death_times.begin(), death_times.end());

    cout<<hours(death_times[0]) << " " << hours(death_times[death_times.size() / 2]) << " " <<
	hours(death_times.back()) << "\n";
}

int main(int argc, char *argv[]) {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin.sync_with_stdio(false);

    for(int n; cin >> n && n > 0; ) {
	algo(n);
    }

    return 0;
}
