#include <algorithm>
#include <boost/foreach.hpp>

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>


typedef CGAL::Exact_predicates_exact_constructions_kernel K;

typedef K::Point_2 P;
typedef K::Segment_2 S;

using namespace std;

// round down to next double
double floor_to_double(const K::FT& x) {
  double a = std::floor(CGAL::to_double(x));
  while (a > x) a -= 1;
  while (a+1 <= x) a += 1;
  return a;
}


void shorten_segment(S& s, const CGAL::Object& o) {
    if (const P* op = CGAL::object_cast<P>(&o)) {
	s = S(s.source(), *op);
    }
    else if(const S* t = CGAL::object_cast<S>(&o)) {
	if (CGAL::collinear_are_ordered_along_line
	    (s.source(), t->source(), t->target()))
	    s = K::Segment_2(s.source(), t->source());
	else
	    s = K::Segment_2(s.source(), t->target());
    }
    else {
	throw int();
    }
}


int main(int argc, char *argv[]) {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin.sync_with_stdio(false);

    vector<S> obstacles;
    for(int n; cin >> n && n > 0;) {
	K::Ray_2 ray; cin >> ray;

	obstacles.clear(); obstacles.reserve(n);
	bool result = false;
	for (int i = 0; i < n; ++i) {
	    S ob; cin >> ob;
	    obstacles.push_back(ob);
	}

	random_shuffle(obstacles.begin(), obstacles.end());
	S segment(ray.source(), ray.source());

	int i = 0;
	for( ; i < n ; ++i) {
	    if(CGAL::do_intersect(ray, obstacles[i])) {
		shorten_segment(segment, CGAL::intersection(ray, obstacles[i]));
		break;
	    }
	}

	if(i == n) {
	    cout << "no\n";
	    continue;
	}

	for( ;i < n; ++i) {
	    if(CGAL::do_intersect(segment, obstacles[i])) {
	    	shorten_segment(segment, CGAL::intersection(segment, obstacles[i]));
	    }
	}

	cout << floor_to_double(segment.target().x()) << " "
	     << floor_to_double(segment.target().y()) << "\n";
    }

    return 0;
}

