#include "Entities.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"

Entity::Entity(sf::Vector2f pos, sf::Shape* shp) {
	this->shp = shp;
	this->shp->setPosition(pos);
}

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
}

void Entity::hit() {
}
