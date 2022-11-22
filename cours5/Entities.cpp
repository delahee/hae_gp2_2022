#include "Entities.hpp"

Entity::Entity(sf::Vector2f pos, sf::Shape* shp) {
	this->shp = shp;
	this->shp->setPosition(pos);
}

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
}

Pad::Pad(sf::Vector2f pos) : Entity(pos, new sf::RectangleShape(sf::Vector2f(164, 24))) {
	auto rect = (sf::RectangleShape*)shp;
	auto bnd = rect->getLocalBounds();
	rect->setOrigin(sf::Vector2f(bnd.width*0.5f,bnd.height*0.5f));
	rect->setFillColor(sf::Color::Red);
	rect->setOutlineColor(sf::Color::Magenta);
	rect->setOutlineThickness(2);
}

static float speed = 6;

void Pad::moveLeft() {
	shp->setPosition(shp->getPosition() + sf::Vector2f(-2 * speed, 0));
}

void Pad::moveRight() {
	shp->setPosition(shp->getPosition() + sf::Vector2f(2 * speed, 0));
}
