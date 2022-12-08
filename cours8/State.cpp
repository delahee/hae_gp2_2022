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


}
