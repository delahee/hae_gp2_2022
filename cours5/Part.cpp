#include "Part.hpp"
#include "Lib.hpp"

void Parts::add(sf::Vector2f pos) {

}

void Parts::update() {

}

void Parts::draw(sf::RenderWindow&win  ) {

}

Part::Part() {
	shp.setOrigin(2, 2);
	shp.setRotation( 360 * Lib::randF());
}
