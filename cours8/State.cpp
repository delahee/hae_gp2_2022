#include "State.hpp"
#include "Entities.hpp"

void StateIdle::onEnterState() {

}

void StateIdle::onEvent(sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Up
			|| event.key.code == sf::Keyboard::Space) {
			owner->dy -= 2.0f;
		}
	}
	
}

void StateIdle::updateState() {
	sf::Vector2f dir(0, 0);
	float sp = 0.15f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		dir.x--;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		dir.x++;
	float len = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len) {
		dir.x /= len;
		dir.y /= len;
		owner->dx += dir.x * sp;
		owner->dy += dir.y * sp;
	}

}
