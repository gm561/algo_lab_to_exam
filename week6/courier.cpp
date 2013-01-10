#include <iostream>
#include <climits>

#include <boost/foreach.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/connected_components.hpp>


using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;

typedef adjacency_list<vecS, vecS, directedS, no_property,
		       property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					 property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef graph_traits <Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;


void add_biedge(int from, int to, int cap_to, Graph& graph) {
    property_map<Graph, edge_capacity_t>::type
	capacity = get(edge_capacity, graph);

    property_map<Graph, edge_reverse_t>::type
	reverese_edge = get(edge_reverse, graph);

    Edge edge, redge; bool inserted;

    tie(edge, inserted) = add_edge(from, to, graph);
    tie(redge, inserted) = add_edge(to, from, graph);

    capacity[edge] = cap_to;
    capacity[redge] = 0;

    reverese_edge[edge] = redge;
    reverese_edge[redge] = edge;
}

int main(int argc, char *argv[]) {
    int TC; cin >> TC;

    for(int tc = 0; tc < TC; ++tc) {
	int Z, J; cin >> Z >> J;

	Graph graph (Z + J + 2);

	const int SINK = Z + J;
	const int SOURCE  = Z + J + 1;

	vector<int> costs(Z);
	for (int i = 0; i < Z; ++i) {
	    int cost; cin >> cost;
	    costs[i] = cost;
	    add_biedge(i + J, SINK, cost, graph);
	}

	vector<int> payment(J);
	for (int i = 0; i < J; ++i) {
	    int income; cin >> income;
	    payment[i] = income;
	    add_biedge(SOURCE, i, income, graph);
	}

	vector<vector<int > > required_tickets(J, vector<int>());
	for (int i = 0; i < J; ++i) {
	    int n; cin >> n;
	    for (int j = 0; j < n; ++j) {
		int zone; cin >> zone; zone -= 1;
		required_tickets[i].push_back(zone);
		add_biedge(i, zone + J, INT_MAX, graph);
	    }
	}

	property_map<Graph, edge_residual_capacity_t>::type
	    residual_capacity = get(edge_residual_capacity, graph);

	property_map<Graph, edge_capacity_t>::type
	    capacity = get(edge_capacity, graph);

	bool run_again = true;

	int revenue = 0;
	vector<int> jobs(J,1);

	while(run_again) {
	    run_again = false;
	    revenue = 0;

	    push_relabel_max_flow(graph, SOURCE, SINK);

	    vector<int> tickets(Z);
	    vector<int> bought_tickets(Z);
	    for(int i = 0; i < Z; ++i) {
		Vertex v0 = vertex(i + J, graph);
		Vertex v1 = vertex(SINK, graph);

		Edge e; bool value;
		tie(e, value) =  edge(v0, v1, graph);

		if(residual_capacity[e] == 0) {
		    tickets[i] = 1;
		}
	    }

	    for(int i = 0; i < J; ++i) {
		bool has_tickets = true;
		BOOST_FOREACH(int zone, required_tickets[i]) {
		    if(!tickets[zone]) {
			has_tickets = false;
			break;
		    }
		}

		if(!has_tickets) {
		    if(jobs[i]) {
			Vertex v0 = vertex(SOURCE, graph);
			Vertex v1 = vertex(i, graph);

			Edge e; bool value;
			tie(e, value) =  edge(v0, v1, graph);
			capacity[e] = 0;
			jobs[i] = 0;
			run_again = true;
		    }
		}
		else {
		    int cost = 0;
		    BOOST_FOREACH(int zone, required_tickets[i]) {
			if(!bought_tickets[zone]) {
			    cost += costs[zone];
			    ++bought_tickets[zone];
			}
		    }

		    revenue += payment[i] - cost;
		}
	    }
	}

	cout << revenue << "\n";
    }

    return 0;
}

