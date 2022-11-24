#include "Entities.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Lib.hpp"
#include "World.hpp"

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

static float speed = 16;

void Pad::moveLeft() {
	shp->setPosition(shp->getPosition() + sf::Vector2f(-2 * speed, 0));
}

void Pad::moveRight() {
	shp->setPosition(shp->getPosition() + sf::Vector2f(2 * speed, 0));
}

Ball::Ball(Pad * p) : Entity(sf::Vector2f(), new sf::CircleShape(12, 12)){
	auto circ = (sf::RectangleShape*)shp;
	circ->setOrigin(12, 12);
	initPos(p);

	circ->setFillColor(sf::Color::Yellow);
	circ->setOutlineColor(sf::Color::Blue);
	circ->setOutlineThickness(2);
}

void Ball::initPos(Pad*hook){
	auto p = hooked = hook;
	if (hook) {
		xOffset = p->getLocalBounds().width * 0.1f;
		yOffset = -p->getLocalBounds().height * 1.0f;
		speed = sf::Vector2f(0, 0);
	}
}


int fr = 0;
void Ball::update() {
	lastPos = shp->getPosition();

	if( hooked )
		shp->setPosition(hooked->getPosition() + sf::Vector2f(xOffset,yOffset));
	else {
		shp->setPosition(shp->getPosition() + speed);
	}

	if( (fr>10) && !hooked){
		particles.add(shp->getPosition());
		fr = 0;
	}
	fr++;

}

Wall::Wall(sf::FloatRect r) : Entity(sf::Vector2f(r.left, r.top),new sf::RectangleShape(sf::Vector2f(r.width,r.height))) {
	auto rect = (sf::RectangleShape*)shp;
	rect->setFillColor(sf::Color::Red);
	rect->setOutlineColor(sf::Color::Green);
	rect->setOutlineThickness(2);
}

Brick::Brick(sf::FloatRect r) : Entity(sf::Vector2f(r.left, r.top), new sf::RectangleShape(sf::Vector2f(r.width, r.height))) {
	auto rect = (sf::RectangleShape*)shp;
	rect->setFillColor( SFML_ORANGE );
	rect->setOutlineColor(sf::Color::Yellow);
	rect->setOutlineThickness(2);
}

void Brick::hit() {
	hitPoint--;
	fr++;
	if (hitPoint <= 0)
		world.toBeDeleted.push_back(this);
}
