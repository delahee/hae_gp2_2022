#include "State.hpp"
#include "Entities.hpp"

inline static bool isCloseTo( float val, float target, float eps = 1e-3){
	return abs(target - val) < eps;
}

void StateIdle::onEnterState() {
	owner->shp->setFillColor(sf::Color::Yellow);
	owner->dx = 0.0f;
	owner->dy = 0.0f;
}

void StateIdle::onEvent(sf::Event& event) {

}

void StateIdle::updateState() {
	owner->walkControl();
	 
	if ( (abs(owner->dx) >=  0.0001f) || (abs(owner->dy) >= 0.0001f) ) {
		owner->changeState(owner->walkState);
	}
}


void StateWalk::onEnterState() {
	owner->shp->setFillColor(sf::Color::Green);

}

void StateWalk::onEvent(sf::Event& event) {
	//owner->jumpControl(event);
}

void StateWalk::updateState() {
	owner->walkControl();
	if (isCloseTo(owner->dx,0) && isCloseTo(owner->dy, 0)) {
		owner->changeState(owner->idleState);
	}
}

void StatePath::onEnterState() {
	owner->shp->setFillColor(sf::Color::Red);
}

void StatePath::onEvent(sf::Event& ev) {

}

void StatePath::updateState() {
	auto& path = owner->curPath;
	if (path.empty()) {
		owner->changeState(owner->idleState);
		return;
	}

	sf::Vector2i next = path[0];
	if( owner->cx == next.x && owner->cy == next.y){
		path.erase(path.begin());
		return;
	}
	else {
		float dirX = next.x - owner->cx;
		float dirY = next.y - owner->cy;

		float len = sqrt(dirX * dirX + dirY * dirY);
		if( len ){
			dirX /= len;
			dirY /= len;
		}
		else{
			path.erase(path.begin());
			return;
		}

		float sp = 0.2;
		owner->dx = dirX * sp;
		owner->dy = dirY * sp;
	}
}
