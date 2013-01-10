#include <algorithm>
#include <vector>
#include <iostream>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

#define PB(x) push_back(x)
#define SIZE(x) (int) x.size()

using namespace std;

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Min_circle_2<CGAL::Min_circle_2_traits_2<K> > MC;

typedef CGAL::Exact_predicates_exact_constructions_kernel EK;
typedef CGAL::Min_circle_2<CGAL::Min_circle_2_traits_2<EK> > EMC;

double ceil_to_double(const EK::FT& x) {
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}

struct Point {
    K::FT distance;
    K::Point_2 p;

    Point(int x, int y) : p(x, y) { }

    bool operator<(const Point& lhs) const  {
	return distance < lhs.distance;
    }

    bool operator>(const Point& lhs) const  {
	return distance > lhs.distance;
    }
};

//radius from the source
inline K::FT radius0(int i, vector<Point> &points) {
    return points[i].distance;
}

//radius for remaning points
inline K::FT radius1(int i, vector<K::Point_2> &points) {
    MC mc(points.begin() + i, points.end(), true);

    return mc.circle().squared_radius();
}

//radius from the source
inline EK::FT radius0E(int i, vector<Point> &points) {
    return EK::FT(points[i].distance);
}

//radius for remaning points
inline EK::FT radius1E(int i, vector<K::Point_2> &points) {
    vector<EK::Point_2> points0; points0.reserve(SIZE(points));

    for(int j = 0; j < SIZE(points); ++j) {
	points0.PB(EK::Point_2(points[j].x(), points[j].y()));
    }

    EMC mc(points0.begin() + i, points0.end(), true);

    return mc.circle().squared_radius();
}

int foo(int a, int b, vector<K::Point_2> &points, vector<Point> &points0) {
    if(b - a <= 1) {
	return a;
    }

    int pivot = (a+b)/2;

    K::FT r0 = radius0(pivot, points0);
    K::FT r1 = radius1(pivot, points);

    if(r0 > r1) {
	return foo(a, pivot, points, points0);
    }
    else {
	return foo(pivot, b, points, points0);
    }

}

void algo(int n) {
    vector<Point> points; points.reserve(n);

    for (int i = 0; i < n; ++i) {
	int x,y; cin >> x >> y;
	points.PB(Point(x,y));
	points.back().distance =
	    CGAL::squared_distance(points.front().p, points.back().p);
    }

    sort(points.begin(), points.end());
    vector<K::Point_2> points2; points2.reserve(n);
    for(int i = 0; i < n; ++i) {
	points2.PB(points[i].p);
    }

    int a = foo(0, n - 1, points2, points);

    EK::FT r0 = radius0E(a, points);
    EK::FT r1 = radius1E(a + 1, points2);

    cout << ceil_to_double(max(r0,r1)) << "\n";
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);

    for(int n = 0; cin >> n && n > 0; ) {
	algo(n);
    }

    return 0;
}
