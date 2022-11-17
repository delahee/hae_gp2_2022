#pragma once
#include <vector>
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Line {
public:
	std::vector<sf::Vector2f> baked;

	Line(){
		baked.push_back(sf::Vector2f(200, 200));
		baked.push_back(sf::Vector2f(300, 250));
		baked.push_back(sf::Vector2f(400, 200));
		baked.push_back(sf::Vector2f(500, 200));
	}

	void draw(sf::RenderWindow& win) {
		sf::VertexArray vb(sf::LineStrip);
		for (auto& b : baked) {
			sf::Vertex vtx(b, sf::Color::Cyan);
			vb.append(vtx);//tout mes vertex;
		}
		win.draw(vb);
	};

	void setPoints(std::vector<sf::Vector2f>& p, float tstep = 0.1f) {
		auto get = [&p](int idx) {
			if (idx < 0) idx = 0;
			if (idx >= p.size())idx = p.size() - 1;
			return p[idx];
		};
		baked.clear();
		int steps = std::round(1.0f / tstep);
		double cstep = 0.0;
		for (int i = 0; i < p.size(); ++i) {
			auto p0 = get(i - 1);
			auto p1 = get(i);
			auto p2 = get(i + 1);
			auto p3 = get(i + 2);
			cstep = 0.0;
			//creer les vertex interpolées entre les courbes.
			while(cstep < 1.0f){
				if (cstep >= 1.0f)
					cstep = 1.0f;
				baked.push_back(Catmull::polynom2(p0, p1, p2, p3, cstep));
				cstep += tstep;
				if (cstep > 1.0f)
					break;
			}
		}
	};
};