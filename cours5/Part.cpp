#include "Part.hpp"
#include "Lib.hpp"
#include "SFML/System/Vector2.hpp"

void PartController::add(sf::Vector2f pos) {
	data.push_back(Part(pos));
}

void PartController::update() {
	for (auto& p : data)
		p.update();
}

void PartController::draw(sf::RenderWindow&win  ) {
	for (auto& p : data)
		p.draw(win);
}

Part::Part() {
	shp.setOrigin(2, 2);
	shp.setRotation( 360 * Lib::randF());
}

Part::Part(sf::Vector2f pos) : Part() {
	shp.setPosition(pos);
}


void Part::draw(sf::RenderWindow& win) {
	win.draw(shp);
}

void Part::update(){
	auto pos = shp.getPosition();
	speed.x = speed.x * 0.98;
	speed.y += 0.1f;

	pos.x += speed.x;
	pos.y += speed.y;
	shp.setPosition(pos);
}
