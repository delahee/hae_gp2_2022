#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Entity{
public:
	sf::Shape*		shp = nullptr;

	Entity(sf::Vector2f pos, sf::Shape* shp);

	auto getLocalBounds() const {
		return shp->getLocalBounds();
	};

	void draw(sf::RenderWindow& win);
};

class Pad : public Entity {
public:
	Pad(sf::Vector2f pos);

	void moveLeft();
	void moveRight();
};