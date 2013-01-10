#include <algorithm>
#include <boost/foreach.hpp>
#include <iostream>
#include <stack>

#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;

typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::All_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;

typedef K::Point_2 Point;
typedef K::Iso_rectangle_2 Rectangle;

using namespace std;

double ceil_to_double(const K::FT& x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

struct User {
    Point p;
    double d;

    User(Point& p_, double d_) : p(p_), d(d_) {}

};

void algo(int n) {

    vector<Point> infected; infected.reserve(n);
    for (int i = 0; i < n; ++i) {
	Point p; cin >> p;
	infected.push_back(p);
    }

    int m; cin >> m;
    vector<User> users; users.reserve(m);
    for (int i = 0; i < m; ++i) {
	Point p; cin >> p;
	double d; cin >> d;
	users.push_back(User(p,d));
    }

    Triangulation dt;
    dt.insert(infected.begin(), infected.end());

    vector<int> results; results.reserve(m);

    for(Face_iterator fi = dt.all_faces_begin(); fi != dt.all_faces_end(); ++fi) {
	fi->info() = 0;
    }

    int i = 0;
    BOOST_FOREACH(User u, users) {
	++i;
	int result = 0;
	Triangulation::Face_handle fh = dt.locate(u.p);
	if(squared_distance(dt.nearest_vertex(u.p)->point(), u.p) < u.d) {
	    result = 0;
	    results.push_back(result);
	    continue;
	}

	stack<Triangulation::Face_handle> face_stack;
	face_stack.push(fh);
	while(!face_stack.empty()) {
	    Face_handle fh = face_stack.top(); face_stack.pop();
	    if(dt.is_infinite(fh)) {
		result = 1;
		break;
	    }

	    for(int j = 0; j < 3; ++j) {
		if(fh->neighbor(j)->info() < i &&
		   dt.segment(fh, j).squared_length() >= 4 * u.d ) {
		    face_stack.push(fh->neighbor(j));
		    fh->neighbor(j)->info() = i;
		}
	    }
	}

	results.push_back(result);
    }


    BOOST_FOREACH(int result, results) {
	cout << ( (result) ? "y" : "n" );
    }

    cout << "\n";
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);

    for(int n; cin >> n && n > 0; ) {
	algo(n);
    }

    return 0;
}
