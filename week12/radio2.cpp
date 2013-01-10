#include <iostream>

#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel_with_sqrt.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>

#include <CGAL/Min_circle_2.h>
#include <CGAL/Min_circle_2_traits_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Exact_predicates_exact_constructions_kernel_with_sqrt EK;
typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<int,K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb,Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds>  Triangulation;

typedef Triangulation::Edge_iterator  Edge_iterator;
typedef Triangulation::Finite_vertices_iterator Vertex_iterator;
typedef Triangulation::Finite_faces_iterator Face_iterator;
typedef Triangulation::Face_handle Face_handle;
typedef Triangulation::Vertex_handle Vertex_handle;


typedef K::Point_2 Point;
typedef K::Circle_2 Circle;

using namespace std;

void algo() {
    //m - #healthy
    //n - #cancer
    int m,n ; cin >> m >> n;

    vector<Point> healthy;
    for (int i = 0; i < m; ++i) {
	double x,y; cin >> x >> y;
	healthy.push_back(Point(x,y));
    }

    vector<Point> cancers;
    for (int i = 0; i < n; ++i) {
	double x,y; cin >> x >> y;
	cancers.push_back(Point(x,y));
    }


    CGAL::spatial_sort(cancers.begin(), cancers.end());
    Triangulation dt;
    dt.insert(healthy.begin(), healthy.end());

    vector<int> checked(m,0);
    int max_cancer_cells = 0;

    Face_handle fh = dt.locate(cancers[0]);
    K::FT distance = squared_distance(dt.nearest_vertex(cancers[0])->point(), cancers[0]);
    Circle c(cancers[0], distance);

    for (int i = 0; i < n; ++i) {
	if(c.has_on_bounded_side(cancers[i])) {
	    ++max_cancer_cells;
	}
    }

//    for(Face_iterator fi = dt.finite_faces_begin(); fi != dt.finite_faces_end(); ++fi) {
    for(int i = 0; i < n; ++i) {
    	int cancer_cells = 0;
	Vertex_handle vh = dt.nearest_vertex(cancers[i], fh);
	fh = vh->face();
	K::FT distance = squared_distance(vh->point(), cancers[i]);
	Circle c(cancers[i], distance);


//	cout << "vertex " << cancers[i] << " radius " << sqrt(distance) << endl;
	for (int j = 0; j < n; ++j) {
	    if(c.has_on_bounded_side(cancers[j])) {
//		cout << "cell is in " << cancers[j] << endl;
		++cancer_cells;
	    }
	}

    	max_cancer_cells = max(cancer_cells, max_cancer_cells);
    }

    cout << max_cancer_cells << "\n";
}

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;
    for (int i = 0; i < TC; ++i) {
	algo();
    }

    return 0;
}

