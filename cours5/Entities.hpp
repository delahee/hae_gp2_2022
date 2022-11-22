#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

class Entity{
public:
	sf::Shape*		shp = nullptr;

	Entity(sf::Vector2f pos, sf::Shape* shp);

	inline auto getLocalBounds() const {
		return shp->getLocalBounds();
	};
	inline auto getPosition() const {
		return shp->getPosition();
	};

	void draw(sf::RenderWindow& win);
};

class Pad : public Entity {
public:
	Pad(sf::Vector2f pos);

	void moveLeft();
	void moveRight();
};

class Ball : public Entity{
public:
	sf::Vector2f speed;
	sf::Vector2f lastPos;

	Pad* hooked = nullptr;
	int xOffset = 0;
	int yOffset = 0;
	Ball(Pad * p);

	void update();
};