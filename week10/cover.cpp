#include <iostream>
#include <boost/foreach.hpp>

using namespace std;

#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Delaunay_triangulation_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
//typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EKS;
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

    while (a*a < x) a += 1;
    while ((a-1)*(a-1) >= x) a -= 1;

    return a;
}

void algo(int n) {

    double x1,x2,y1,y2;
    cin >> x1 >> y1 >> x2 >> y2;

    vector<Segment> segments; segments.reserve(4);
    segments.PB(Segment(Point(x1, y1), Point(x1,y2)));
    segments.PB(Segment(Point(x1, y1), Point(x2,y1)));
    segments.PB(Segment(Point(x2, y2), Point(x1,y2)));
    segments.PB(Segment(Point(x2, y2), Point(x2,y1)));

    Rectangle rec(Point(x1,y1), Point(x2,y2));
    vector<Point> points; points.reserve(n);

    for (int i = 0; i < n; ++i) {
	double x,y; cin >> x >> y;
	points.PB(Point(x,y));
    }

    Triangulation dt;
    dt.insert(points.begin(), points.end());

    K::FT max_radius = 0;

    Point p0(x1,y1);
    Point p = dt.nearest_vertex(p0)->point();
    max_radius = max(squared_distance(p, p0), max_radius);

    Point p1(x1,y2);
    p = dt.nearest_vertex(p1)->point();
    max_radius = max(squared_distance(p, p1), max_radius);

    Point p2(x2,y2);
    p = dt.nearest_vertex(p2)->point();
    max_radius = max(squared_distance(p, p2), max_radius);

    Point p3(x2,y1);
    p = dt.nearest_vertex(p3)->point();
    max_radius = max(squared_distance(p, p3), max_radius);

    for (Face_iterator f = dt.finite_faces_begin(); f != dt.finite_faces_end(); ++f) {
    	Point vp = dt.dual(f);
	if(rec.has_on_bounded_side(vp)) {
	    Point dp = f->vertex(0)->point();
	    max_radius = max(CGAL::squared_distance(vp, dp), max_radius);
	}
	else {
	    for(int i = 0; i < 3; ++i) {
		Triangulation::Edge_circulator ec = dt.incident_edges(f->vertex(i), f);
		do {
		    Edge edge = *ec;
		    Segment seg = dt.segment(edge);
		    bool valid = false;
		    for(int j = 0; j < 3 && !valid; ++j) {
			if(i != j) {
			    valid = (seg.source() == f->vertex(j)->point() ||
				     seg.target() == f->vertex(j)->point());
			}
		    }

		    if(!valid) continue;
		    CGAL::Object o = dt.dual(edge);
		    if(const Segment *so = CGAL::object_cast<Segment>(&o)) {
			if(CGAL::do_intersect(*so, seg)) {
			    CGAL::Object o0 = CGAL::intersection(*so, seg);
			    if(const Point *p = CGAL::object_cast<Point>(&o0)) {
				max_radius = max(squared_distance(*p, seg.source()), max_radius);
				max_radius = max(squared_distance(*p, seg.target()), max_radius);
			    }
			    else {
				throw int();
			    }

			    continue;
			}
		    }
		    else if(const Ray *ro = CGAL::object_cast<Ray>(&o)) {
			if(CGAL::do_intersect(*ro, seg)) {
			    CGAL::Object o0 = CGAL::intersection(*ro, seg);
			    if(const Point *p = CGAL::object_cast<Point>(&o0)) {
				max_radius = max(squared_distance(*p, seg.source()), max_radius);
				max_radius = max(squared_distance(*p, seg.target()), max_radius);
			    }
			    else {
				throw int();
			    }

			    continue;
			}

		    }
		}
		while(++ec != dt.incident_edges(f->vertex(i), f));
	    }
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
			EK::Ray_2 ray(EK::Point_2(r->source().x(), r->source().y()),
				      EK::Point_2(r->point(1).x(), r->point(1).y()));
			EK::Segment_2 seg0(EK::Point_2(s.source().x(), s.source().y()),
					  EK::Point_2(s.target().x(), s.target().y()));
			CGAL::Object o1 = CGAL::intersection(ray, seg0);

			if(const EK::Point_2 *p = CGAL::object_cast<EK::Point_2>(&o1)) {
			    Point po(CGAL::to_double(p->x()),
				     CGAL::to_double(p->y()));

			    max_radius = max(squared_distance(seg.target(), po),
			    		     max_radius);
			}
			else {
			    throw int();
			}
		    }
    		}
    	    }
    	}
    	else {
    	    throw int();
    	}
    }

    cout << ceil_to_sqrt_double(max_radius) << "\n";
}

int main(int argc, char *argv[]) {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin.sync_with_stdio(false);

    for(int n; cin >> n && n > 0; ) {
	algo(n);
    }

    return 0;
}

