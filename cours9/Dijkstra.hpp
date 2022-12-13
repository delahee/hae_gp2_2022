#pragma once

#include <unordered_map>
#include <algorithm>

#include "SFML/System/Vector2.hpp"

namespace std {
	template <> struct hash<sf::Vector2i> {
		inline std::size_t operator()(const sf::Vector2i& k) const {
			using std::hash;
			return std::size_t((k.y * 16 * 1024) + k.x);
		};
	};
}

typedef std::unordered_map<sf::Vector2i, bool> BaseGraph;

class Dijkstra{
public:
	BaseGraph g;

	Dijkstra(BaseGraph& _g) {
		g = _g;
	};
};