#include <iostream>               
#include <utility>                   
#include <algorithm>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <random>

#include <typeinfo>
/*THIS IS HUAWEI TASK 2
* DO NOT MESS THIS WITH FIRST FILE
* AND DO NOT OVERRIDE IT
*/
/*
double delay(std::normal_distribution<double>& d, std::mt19937& gen){
	double temp = d(gen);
	return temp < 0 ? 0:temp;
}
double loss(std::vector<double>& losses, std::discrete_distribution<>& d, std::mt19937& gen)
{
	int temp = d(gen);

	if (temp >= losses.size() || temp < 0) {
		return 0;
	}
	return losses[temp];
}

typedef boost::property<boost::edge_weight_t, std::pair<double, double>> EdgeWeightProperty;
typedef boost::property<boost::vertex_property_tag, double> VertexProperty;

//typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> Graph;
//typedef boost::adjacency_list<boost::listS, boost::vecS, boost::undirectedS, VertexProperty, EdgeWeightProperty> Graph;
typedef boost::adjacency_list< boost::listS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> Graph;

typedef boost::graph_traits<Graph>::vertex_iterator vertex_iter;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;

const EdgeWeightProperty DistInf (std::pair<double,double> (std::numeric_limits<double>::infinity(), std::numeric_limits<double>::infinity()) );
const EdgeWeightProperty DistZero (std::pair<double, double>(0, 0));

bool delayLess(EdgeWeightProperty& left, EdgeWeightProperty& right)
{
	if (left.m_value.first < right.m_value.first)
	{
		return true;
	}
	return false;
}

bool lossesLess(EdgeWeightProperty& left, EdgeWeightProperty& right)
{
	if (left.m_value.second < right.m_value.second)
	{
		return true;
	}
	return false;
}

EdgeWeightProperty combineWeights(EdgeWeightProperty& left, EdgeWeightProperty& right)
{
	EdgeWeightProperty ans;
	ans.m_value.first = left.m_value.first + right.m_value.first;
	ans.m_value.second = left.m_value.second + right.m_value.second;
	return ans;
}
*/
/*EdgeWeightProperty randomizeWeight(std::normal_distribution<double>& nd, std::vector<double>losses, std::discrete_distribution<>& dd, std::mt19937& gen)
{

}*/

/*int main()
{
	std::vector<double> losses = { 0, 0.01, 0.02, 0.03, 0.04, 0.05 };
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<double> norm_d {7.5, 1.25};
	std::discrete_distribution<> discr_d( { 0.5, 0.1, 0.1, 0.1, 0.1, 0.1 });
	
	//loss(losses, discr_d, gen);
	//delay(norm_d, gen);

	Graph G(32 * 32);
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 31; j++)
		{
			add_edge(i * 32 + j, i * 32 + j + 1, std::pair<double, double>({ delay(norm_d, gen), loss(losses, discr_d, gen) }), G);

			if (i < 31){
				add_edge(i * 32 + j, (i + 1) * 32 + j, std::pair<double, double>({ delay(norm_d, gen), loss(losses, discr_d, gen) }), G);
			}
		}
		if (i < 31) {
			add_edge(i * 32 + 31, (i + 1) * 32 + 31, std::pair<double, double>({ delay(norm_d, gen), loss(losses, discr_d, gen) }), G);
		}
	}

	boost::property_map< Graph, boost::edge_weight_t >::type weightmap = get(boost::edge_weight, G);
	std::vector<vertex_descriptor> p(num_vertices(G));
	std::vector<int> d(num_vertices(G));
	vertex_descriptor s = vertex(0, G);
	boost::default_dijkstra_visitor vis;

	/*boost::dijkstra_shortest_paths(G, s, p, predecessor_map(boost::make_iterator_property_map(
		p.begin(), get(boost::vertex_index, G))), predecessor_map(boost::make_iterator_property_map(
		p.begin(), get(boost::vertex_index, G))).distance_map(boost::make_iterator_property_map(
			d.begin(), get(boost::vertex_index, G))), weightmap, get(boost::vertex_index, G), delayLess, combineWeights, DistInf, DistZero);
	boost::dijkstra_shortest_paths(G, s, vis, predecessor_map(boost::make_iterator_property_map(
		p.begin(), get(boost::vertex_index, G))), predecessor_map(boost::make_iterator_property_map(
			p.begin(), get(boost::vertex_index, G))).distance_map(boost::make_iterator_property_map(
				d.begin(),get(boost::vertex_index, G))), weightmap, get(boost::vertex_index, G), delayLess, combineWeights, DistInf, DistZero);

	
	return 1;
}*/