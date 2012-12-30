#include <iostream>

#include <boost/foreach.hpp>

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>

#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Min_circle_2<CGAL::Min_circle_2_traits_2<K> > MC;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Min_circle_2<CGAL::Min_circle_2_traits_2<EK> > EMC;

using namespace std;

double ceil_to_double(const EK::FT& x)
{
    double a = std::ceil(CGAL::to_double(x));
    while (a < x) a += 1;
    while (a-1 >= x) a -= 1;
    return a;
}


int main(int argc, char *argv[]) {
    std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(0);
    cin.sync_with_stdio(false);

    vector<K::Point_2> points;
    for(int n; cin >> n && n > 0; ) {
	points.clear(); points.reserve(n);
	for (int i = 0; i < n; ++i) {
	    K::Point_2 p; cin >> p; points.push_back(p);
	}

	MC mc(points.begin(), points.end(), true);

	EK::Point_2 spt[3];
	for (std::size_t i = 0; i < mc.number_of_support_points(); ++i)
	    spt[i] = EK::Point_2(mc.support_point(i).x(), mc.support_point(i).y());

	EMC emc(spt, spt + mc.number_of_support_points());

	cout << ceil_to_double(sqrt(emc.circle().squared_radius())) << "\n";
    }

    return 0;
}
