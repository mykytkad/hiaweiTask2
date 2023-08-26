#include <iostream>               
#include <utility>                   
#include <algorithm>
#include <boost/config.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

/*THIS IS HUAWEI TASK 2
* DO NOT MESS THIS WITH FIRST FILE
* AND DO NOT OVERRIDE IT
*/
using namespace std;
using namespace boost;

typedef pair<float, float> normDistribution;
typedef vector<pair<float, float>> lossDistribution;
typedef boost::property<boost::edge_weight_t, pair<normDistribution, lossDistribution>> EdgeWeightProperty;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, boost::no_property, EdgeWeightProperty> Graph;
typedef graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<Graph>::vertex_descriptor vertex_descriptor;

const EdgeWeightProperty Distinf(pair<normDistribution, lossDistribution>
	(normDistribution(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity()), lossDistribution( {pair<float, float>(0,1)} )));

const EdgeWeightProperty Distzero(pair<normDistribution, lossDistribution> (normDistribution(0, 0), lossDistribution( {pair<float, float>(0,1)} )));

bool compareWeights(EdgeWeightProperty left, EdgeWeightProperty right)
{
	if (left.m_value.first.first < right.m_value.first.first)
	{
		return false;
	}
	if (left.m_value.first.first == right.m_value.first.first)
	{
		return (left.m_value.first.second > right.m_value.first.second);
	}
	return true;
}
lossDistribution addLossDistributions(lossDistribution l, lossDistribution r)
{
	map<float, float> m;
	for (auto p_l: l)
	{
		for (auto p_r : r)
		{
			//float sum_loss  = p_l.first + p_r.first;
			//float prob_loss = p_l.second * p_r.second;
			m[p_l.first + p_r.first] += p_l.second * p_r.second;
		}
	}
	lossDistribution ans;
	for (auto p : m)
	{
		ans.push_back(pair<float, float>(p.first, p.second));
	}
	return ans;
}
EdgeWeightProperty combineWeights(EdgeWeightProperty left, EdgeWeightProperty right)
{
	left.m_value.first.first += right.m_value.first.first;
	left.m_value.first.second += right.m_value.first.second;
	left.m_value.second = addLossDistributions(left.m_value.second, right.m_value.second);
	return left;
}


/*int main()
{
	Graph G(32*32);
	lossDistribution loss = { {0,0.5},{0.001, 0.1},{0.002, 0.1}, {0.003, 0.1}, {0.004, 0.1}, {0.005, 0.1} };
	normDistribution nd = { 7.5, 1.25 };
	EdgeWeightProperty weight(pair<normDistribution, lossDistribution>(nd, loss));
	//boost::graph_traits<Graph>::vertex_iterator vi, vi_end, next;
	//boost::tie(vi, vi_end) = vertices(G);
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 31; j++)
		{
			add_edge(i * 32 + j, i * 32 + j + 1, weight, G);
			if (i < 31) add_edge(i * 32 + j, (i + 1) * 32 + j, weight, G);
		}
		if (i < 31) add_edge(i * 32 + 31, (i + 1) * 32 + 31, weight, G);
	}
	property_map< Graph, edge_weight_t >::type weightmap = get(edge_weight, G);
	vector< vertex_descriptor > p(num_vertices(G));
	vector< int > d(num_vertices(G));
	vertex_descriptor s = vertex(0, G);
	boost::dijkstra_shortest_paths(G, s, predecessor_map(boost::make_iterator_property_map(
		p.begin(), get(boost::vertex_index, G))).distance_map(boost::make_iterator_property_map(
			d.begin(), get(boost::vertex_index, G))), weightmap, get(vertex_index, G), compareWeights, combineWeights, Distinf, Distzero, );

	return 1;
}*/