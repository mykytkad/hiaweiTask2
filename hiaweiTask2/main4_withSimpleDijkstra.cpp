#include <iostream>               
#include <utility>                   
#include <algorithm>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/property_map/property_map.hpp>
#include <random>

#include <typeinfo>

double delay(std::normal_distribution<double>& d, std::mt19937& gen) {
	double temp = d(gen);
	return temp < 0 ? 0 : temp;
}

double loss(std::vector<double>& losses, std::discrete_distribution<>& d, std::mt19937& gen)
{
	int temp = d(gen);

	if (temp >= losses.size() || temp < 0) {
		return 0;
	}
	return losses[temp];
}

typedef boost::property<boost::edge_weight_t, double> EdgeWeightProperty;
typedef boost::property<boost::vertex_distance_t, double> Distance;
typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS, Distance, EdgeWeightProperty> Graph;

typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;




int main()
{
	const int N = 32;
	std::vector<double> losses = { 0, 0.01, 0.02, 0.03, 0.04, 0.05 };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> norm_d {7.5, 1.25};
	std::discrete_distribution<> discr_d({ 0.5, 0.1, 0.1, 0.1, 0.1, 0.1 });


	Graph G_delay(N * N);
	Graph G_loss(N * N);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			add_edge(i * N + j, i * N + j + 1,  delay(norm_d, gen), G_delay);
			add_edge(i * N + j, i * N + j + 1, loss(losses, discr_d, gen), G_loss);
			if (i < N - 1) {
				add_edge(i * N + j, (i + 1) * N + j, delay(norm_d, gen), G_delay);
				add_edge(i * N + j, (i + 1) * N + j, loss(losses, discr_d, gen), G_loss);
			}
		}
		if (i < 31) {
			add_edge(i * N + (N - 1), (i + 1) * N + (N - 1), delay(norm_d, gen), G_delay);
			add_edge(i * N + (N - 1), (i + 1) * N + (N - 1), loss(losses, discr_d, gen), G_loss);
		}
	}


    boost::property_map< Graph, boost::edge_weight_t >::type weightmap = get(boost::edge_weight, G_delay);
    std::vector< vertex_descriptor > parents_delay(num_vertices(G_delay));
    std::vector< double > distance_delay(num_vertices(G_delay));
    vertex_descriptor s = vertex(2, G_delay);
	auto predecessor = boost::predecessor_map(boost::make_iterator_property_map(parents_delay.begin(), get(boost::vertex_index, G_delay))).distance_map(boost::make_iterator_property_map(
		distance_delay.begin(), get(boost::vertex_index, G_delay)));
  
	boost::dijkstra_shortest_paths(G_delay, s, predecessor);

	weightmap = get(boost::edge_weight, G_loss);
	std::vector< vertex_descriptor > parents_loss(num_vertices(G_loss));
	std::vector< double > distance_loss(num_vertices(G_loss));
	s = vertex(2, G_loss);
	predecessor = boost::predecessor_map(boost::make_iterator_property_map(parents_loss.begin(), get(boost::vertex_index, G_loss))).distance_map(boost::make_iterator_property_map(
		distance_loss.begin(), get(boost::vertex_index, G_loss)));

	boost::dijkstra_shortest_paths(G_loss, s, predecessor);
    std::cout << "distances and parents:" << std::endl;
    boost::graph_traits< Graph >::vertex_iterator vi, vend;
    
	/*for (boost::tie(vi, vend) = vertices(G_loss); vi != vend; ++vi)
    {
        std::cout << "distance(" << *vi << ") = " << distance_loss[*vi] << ", ";
		std::cout << "parent(" << *vi << ") = " << parents_loss[*vi] << ", ";
		std::cout << "distance(" << *vi << ") = " << distance_delay[*vi] << ", ";
		std::cout << "parent(" << *vi << ") = " << parents_delay[*vi]
            << std::endl;
    }*/
	auto edges = boost::in_edges(2, G_loss);
	std::cout << "edge inner = " << get(boost::edge_weight_t(), G_loss, boost::edge(1,2,G_loss).first) << std::endl;
	
	
	Graph delaySPT(N * N); //with losses as edge weight
	for (int i = 0; i < parents_delay.size(); i++)
	{
		if (i == parents_delay[i]) { //parent vertex of the root vertex of Dijkstra is root vertex
			continue;
		}
		add_edge(i, parents_delay[i], get(boost::edge_weight_t(), G_loss, boost::edge(i, parents_delay[i], G_loss).first), delaySPT);
	}
	weightmap = get(boost::edge_weight, delaySPT);
	std::vector< vertex_descriptor > parents_spt(num_vertices(delaySPT));
	std::vector< double > distance_spt(num_vertices(delaySPT));
	s = vertex(2, delaySPT);
	predecessor = boost::predecessor_map(boost::make_iterator_property_map(parents_loss.begin(), get(boost::vertex_index, delaySPT))).distance_map(boost::make_iterator_property_map(
		distance_loss.begin(), get(boost::vertex_index, delaySPT)));
	boost::dijkstra_shortest_paths(delaySPT, s, predecessor);
	
	int optimal_routes_num = 0;
	for (int i = 0; i < distance_spt.size(); i++)
	{
		if (distance_spt[i] == distance_loss[i]) {
			optimal_routes_num++;
		}
	}
	std::cout << "same routes = " << optimal_routes_num << std::endl;
	return 0;
}