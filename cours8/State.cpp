#include "State.hpp"
#include "Entities.hpp"


static float FRICTX_GROUNDCONTROL = 0.9;
static float FRICTX_AIRCONTROL = 0.75;
inline static bool isCloseTo( float val, float target, float eps = 1e-3){
	return abs(target - val) < eps;
}

void StateIdle::onEnterState() {
	owner->shp->setFillColor(sf::Color::Yellow);
	owner->applyGravity = false;
	owner->dx = 0;
	owner->dy = 0;
	owner->frictX = FRICTX_GROUNDCONTROL;
}

void StateIdle::onEvent(sf::Event& event) {
	owner->jumpControl(event);
}

void StateIdle::updateState() {
	owner->walkLeftRightControl();
	if ((abs(owner->dy) >= 0.01f))
		owner->changeState(owner->jumpState);
	else 
		if (owner->dx != 0) {
			if ((abs(owner->dy) >= 0.01f))
				owner->changeState(owner->walkState);
			else
				owner->changeState(owner->jumpState);
		}
}

void StateJump::onEnterState() {
	owner->shp->setFillColor(sf::Color::Magenta);
	owner->applyGravity = true;
	owner->frictX = FRICTX_AIRCONTROL;

}


void StateJump::onEvent(sf::Event& event) {
	//no jump control

	//coyote time
	if(		(owner->stateLife <= 3.0f)
		&&	!(owner->dy < 0 )){
		owner->jumpControl(event);
	}
}

void StateJump::updateState() {
	owner->walkLeftRightControl();
	if (		owner->collides(owner->cx, owner->cy + 1)
			&&	isCloseTo(owner->dy,0)
		){
		owner->changeState(owner->walkState);
	}
}

void StateWalk::onEnterState() {
	owner->shp->setFillColor(sf::Color::Green);
	owner->applyGravity = false;
	owner->frictX = FRICTX_GROUNDCONTROL;

}

void StateWalk::onEvent(sf::Event& event) {
	owner->jumpControl(event);
}

void StateWalk::updateState() {
	owner->walkLeftRightControl();
	if (isCloseTo(owner->dx,0) && isCloseTo(owner->dy, 0)) {
		owner->changeState(owner->idleState);
	}
	else {
		if (!owner->collides(owner->cx, owner->cy + 1)){
			owner->changeState(owner->jumpState);
		}
	}
}


