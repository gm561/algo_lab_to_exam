#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include <boost/foreach.hpp>

#include <boost/graph/push_relabel_max_flow.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;

typedef adjacency_list_traits<vecS, vecS, directedS> Traits;

typedef adjacency_list<vecS, vecS, directedS, no_property,
		       property<edge_capacity_t, long,
				property<edge_residual_capacity_t, long,
					 property<edge_reverse_t, Traits::edge_descriptor> > > > Graph;

typedef property_map<Graph, edge_capacity_t>::type EdgeCapacityMap;
typedef property_map<Graph, edge_reverse_t>::type ReverseEdgeMap;
typedef property_map<Graph, edge_residual_capacity_t>::type ResidualCapacityMap;
typedef graph_traits<Graph>::edge_descriptor Edge;
typedef graph_traits <Graph>::vertex_descriptor Vertex;

struct Team {
    string name;
    int number;
    int points;
    int to_win;
    int to_play;

    Team() { }

    Team(const string& name_, int number_, int points_)
	: name(name_), number(number_), points(points_), to_win(0), to_play(0)
	{ }
};

int main(int argc, char *argv[]) {
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);

    int TC; cin >> TC;

    vector<Team> teams;
    map<string, Team> team_names;

    for (int tc = 0; tc < TC; ++tc) {
	//number of teams
	int t; cin >> t;
	teams.clear(); teams.reserve(t);
	//remaing matchups
	int m; cin >> m;
	for (int i = 0; i < t; ++i) {
	    int points; cin >> points;
	    string name; cin >> name;
	    Team team = Team(name, i, points);
	    teams.push_back(team);
	    team_names.insert(make_pair(name, team));
	}

	Graph graph(t+2);

	EdgeCapacityMap capacity = get(edge_capacity, graph);
	ReverseEdgeMap rev_edge = get(edge_reverse, graph);
//	ResidualCapacityMap res_capacity = get(edge_residual_capacity, graph);

	for (int i = 0; i < m; ++i) {
	    string name0, name1, empty;
	    cin>>name0; cin >> empty; cin>>name1;

	    Team t0 = team_names[name0];
	    Team t1 = team_names[name1];

	    teams[t0.number].to_win += 1;
	    teams[t1.number].to_win += 1;
	    teams[t0.number].to_play +=1;

	    Edge edge; bool inserted; Edge reverse_edge;
	    tie(edge, inserted)  =
		add_edge(t0.number, t1.number, graph); assert(inserted);
	    tie(reverse_edge, inserted) =
		add_edge(t1.number, t0.number, graph); assert(inserted);

	    capacity[edge] = 1;
	    capacity[reverse_edge] = 0;

	    rev_edge[edge] = reverse_edge;
	    rev_edge[reverse_edge] = edge;
	    //add edge
	}

	//source t
	for(int i = 0; i < t; ++i) {
	    Edge edge; bool inserted; Edge reverse_edge;
	    tie(reverse_edge, inserted) =
	    	add_edge(i, t, graph); assert(inserted);

	    tie(edge, inserted)  =
	    	add_edge(t, i, graph); assert(inserted);

	    rev_edge[edge] = reverse_edge;
	    rev_edge[reverse_edge] = edge;

	    capacity[edge] = teams[i].to_play + teams[i].points;
	    capacity[reverse_edge] = 0;
	}

	for(int i = 0; i < t; ++i) {
	    Edge edge; bool inserted; Edge reverse_edge;
	    tie(edge, inserted)  =
		add_edge(i, t + 1, graph); assert(inserted);

	    tie(reverse_edge, inserted) =
		add_edge(t + 1, i, graph); assert(inserted);

	    capacity[edge] = 0;
	    capacity[reverse_edge] = 0;
	    rev_edge[edge] = reverse_edge;
	    rev_edge[reverse_edge] = edge;
	}

	Vertex source = vertex(t, graph);
	Vertex sink = vertex(t+1,graph);

	long max_flow_to_win = 0;
	for(int i = 0; i < t; ++i) {
	    max_flow_to_win += teams[i].points + teams[i].to_play;
	}

	vector<string> solution; solution.reserve(t);
	for(int i = 0; i < t; ++i) {
	    long max_points = teams[i].to_win + teams[i].points;
	    // cout<<"to win " << teams[i].to_win<<endl;
	    // cout<<"to play " << teams[i].to_play<<endl;
	    // cout<<"Team "<<teams[i].name<< " ";
	    for(int j = 0; j < t; ++j) {
		Edge edge; bool result;
		tie(edge, result) = boost::edge(j, t+1, graph);
		capacity[edge] = max_points;
	    }

	    long flow = push_relabel_max_flow(graph, source, sink);

	    // cout<<"Scores at most ";
	    // cout<<flow<<endl;

	    // cout<<"Solution ";
	    if(flow == max_flow_to_win) {
		solution.push_back(teams[i].name);
	    }
	}

	sort(solution.begin(), solution.end());
	BOOST_FOREACH(string team, solution) {
	    cout<<team<< " ";
	}
	cout<<"\n";
    }

    return 0;
}
