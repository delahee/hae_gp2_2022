#include "Dijkstra.hpp"

float Dijkstra::heur(const sf::Vector2i & s1, const sf::Vector2i & s2) {
	float dx = s2.x - s1.x;
	float dy = s2.y - s1.y;
	return sqrt(dx * dx + dy * dy);
}

std::vector<sf::Vector2i> Dijkstra::getPath(sf::Vector2i dest) {
	if (g.find(dest) == g.end())
		return {};

	std::vector<sf::Vector2i> res;
	sf::Vector2i cur = dest;
	while( cur != start){
		res.push_back(cur);

		if( pred.find(cur) == pred.end())//at some point there is a path rupture
			return {};
		
		sf::Vector2i next = pred[cur];
		if (next == cur) {
			res.clear();
			break;
		}
		cur = next;
	}
	res.push_back(start);
	return res;
}

void Dijkstra::updateDist(const sf::Vector2i & s1, const sf::Vector2i & s2) {
	float ndist = d[s1] + heur(s1, s2);
	if (d[s2] > ndist) {
		d[s2] = ndist;
		pred[s2] = s1;
	}
}

void Dijkstra::build(sf::Vector2i _start) {
	init(_start);
	VertexList q;
	q.resize(g.size());
	for (auto& p : g)
		q.push_back(p.first);

	const int nbNei = 8;
	sf::Vector2i tldr[nbNei] = {
		sf::Vector2i(0,1),
		sf::Vector2i(0,-1),
		sf::Vector2i(1,0),
		sf::Vector2i(-1,0),

		/*
		sf::Vector2i(1,1),
		sf::Vector2i(-1,-1),
		sf::Vector2i(1,-1),
		sf::Vector2i(-1,1),
		*/
	};

	sf::Vector2i s2;
	sf::Vector2i s1;
	while (!q.empty()) {
		int s1Idx = findMin(q);
		if (s1Idx == -1) break;

		s1 = q[s1Idx];
		q.erase(q.begin() + s1Idx);

		for (int i = 0; i < nbNei; ++i) {
			s2 = tldr[i] + s1;
			if (g.find(s2) == g.end()) continue;
			updateDist(s1, s2);
		}
	}
}
