#pragma once
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Line {
public:
	std::vector<sf::Vector2f> baked;

	void setPoints(std::vector<sf::Vector2f> & p, float tstep = 0.1f) {
		auto get = [&p](int idx) {
			if (idx < 0)idx = 0;
			if (idx >= p.size())idx = p.size() - 1;
			return p[idx];
		};
		baked.clear();
		double steps = std::ceil(1.0f / tstep);
		double cstep = 0.0;
		for (int i = 0; i < p.size();++i) {
			auto p0 = get(i - 1);
			auto p1 = get(i);
			auto p2 = get(i + 1);
			auto p3 = get(i + 2);
			cstep = 0.0;
			//creer les vertex interpolées entre les courbes.

			//
		}
	};

	void draw(sf::RenderWindow& win) {

	};
};