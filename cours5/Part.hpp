#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/RenderWindow.hpp"


struct Part{
	int					life = 0;
	sf::RectangleShape	shp = sf::RectangleShape(sf::Vector2f(4, 4));

	Part();
};

class Parts{
public:
	std::vector<Part> data;

	void add(sf::Vector2f pos);
	void update();
	void draw(sf::RenderWindow& win);
};
