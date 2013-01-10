#include <iostream>
#include <boost/foreach.hpp>

using namespace std;

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Delaunay_triangulation_2<K>  Triangulation;

typedef Triangulation::Edge Edge;
typedef Triangulation::Edge_iterator Edge_iterator;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::Finite_faces_iterator Face_iterator;

typedef K::Point_2 Point;
typedef K::Iso_rectangle_2 Rectangle;
typedef K::Segment_2 Segment;
typedef K::Ray_2 Ray;
typedef K::Line_2 Line;

#define PB(x) push_back(x)


double ceil_to_sqrt_double(const K::FT& x) {
    EK::FT xn = sqrt(EK::FT(CGAL::to_double(x)));
    double a = ceil(CGAL::to_double(xn));

    while (a < xn) a += 1;
    while (a-1 >= xn) a -= 1;

    return a;
}

void algo(int n) {

    double x1,x2,y1,y2;
    cin >> x1 >> y1 >> x2 >> y2;

    vector<Segment> segments; segments.reserve(4);
    Point p0(x1, y1), p1(x1, y2), p2(x2, y1), p3(x2, y2);
    Rectangle rec(p0, p3);

    segments.PB(Segment(p0, p1));
    segments.PB(Segment(p0, p2));
    segments.PB(Segment(p3, p1));
    segments.PB(Segment(p3, p2));

    vector<Point> points; points.reserve(n + 4);
    points.PB(p0); points.PB(p1); points.PB(p2); points.PB(p3);

    for (int i = 0; i < n; ++i) {
    	double x,y; cin >> x >> y;
    	points.PB(Point(x,y));
    }

    Triangulation dt;
    dt.insert(points.begin(), points.end());

    K::FT max_radius = 0;

    max_radius = max(squared_distance(p0, dt.nearest_vertex(p0)->point()), max_radius);
    max_radius = max(squared_distance(p1, dt.nearest_vertex(p1)->point()), max_radius);
    max_radius = max(squared_distance(p2, dt.nearest_vertex(p2)->point()), max_radius);
    max_radius = max(squared_distance(p3, dt.nearest_vertex(p3)->point()), max_radius);

    for (Face_iterator f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
    	Point vp = dt.dual(f);
    	if(rec.has_on_bounded_side(vp)) {
    	    Point dp = f->vertex(0)->point();
    	    max_radius = max(CGAL::squared_distance(vp, dp), max_radius);
    	}
    }

    for (Edge_iterator e = dt.finite_edges_begin(); e != dt.finite_edges_end(); ++e) {
    	CGAL::Object o = dt.dual(e);

	Segment seg = dt.segment(*e);
    	if (const Segment *os = CGAL::object_cast<Segment>(&o)) {
    	    BOOST_FOREACH(Segment s, segments) {
    		if(CGAL::do_intersect(*os, s)) {
    		    CGAL::Object o0 = CGAL::intersection(*os, s);
    		    if(const Point *p = CGAL::object_cast<Point>(&o0)) {
    			max_radius = max(squared_distance(seg.target(), *p),
    					max_radius);
    		    }
		    else {
			throw int();
		    }
    		}
    	    }
    	}
    	else if(const Line *ol = CGAL::object_cast<Line>(&o)) {
    	    BOOST_FOREACH(Segment s, segments) {
    		if(CGAL::do_intersect(*ol, s)) {
    		    CGAL::Object o0 = CGAL::intersection(*ol, s);
    		    if(const Point *p = CGAL::object_cast<Point>(&o0)) {
    			max_radius = max(squared_distance(seg.target(), *p),
    					max_radius);
    		    }
		    else {
			throw int();
		    }
    		}
    	    }
    	}
    	else if(const Ray *r = CGAL::object_cast<Ray>(&o)) {
    	    BOOST_FOREACH(Segment s, segments) {
    		if(CGAL::do_intersect(*r, s)) {
    		    CGAL::Object o0 = CGAL::intersection(*r, s);
    		    if(const Point *p = CGAL::object_cast<Point>(&o0)) {
    			max_radius = max(squared_distance(seg.target(), *p),
    					max_radius);
    		    }
		    else {
			throw int();
		    }
		    // else {
		    // 	EK::Ray_2 ray(EK::Point_2(r->source().x(), r->source().y()),
		    // 		      EK::Point_2(r->point(1).x(), r->point(1).y()));
		    // 	EK::Segment_2 seg0(EK::Point_2(s.source().x(), s.source().y()),
		    // 			  EK::Point_2(s.target().x(), s.target().y()));
		    // 	CGAL::Object o1 = CGAL::intersection(ray, seg0);

		    // 	if(const EK::Point_2 *p = CGAL::object_cast<EK::Point_2>(&o1)) {
		    // 	    Point po(CGAL::to_double(p->x()),
		    // 		     CGAL::to_double(p->y()));

		    // 	    max_radius = max(squared_distance(seg.target(), po),
		    // 	    		     max_radius);
		    // 	}
		    // 	else {
		    // 	    throw int();
		    // 	}
		    // }
    		}
    	    }
    	}
    	else {
    	    throw int();
    	}
    }

    cout << max_radius << "\n";
}

int main(int argc, char *argv[]) {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin.sync_with_stdio(false);

    for(int n; cin >> n && n > 0; ) {
	algo(n);
    }

    return 0;
}


