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
	
	inline auto getGlobalBounds() const {
		return shp->getGlobalBounds();
	};
	inline auto getPosition() const {
		return shp->getPosition();
	};
	
	inline void setPosition(const sf::Vector2f& v) {
		shp->setPosition(v);
	};

	void draw(sf::RenderWindow& win);

	virtual void hit();
};
