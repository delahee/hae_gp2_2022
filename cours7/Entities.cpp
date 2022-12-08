#include "Entities.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Lib.hpp"
#include "World.hpp"
#include "Game.hpp"
#include "imgui.h"

Entity::Entity(sf::Vector2f pixelPos, sf::Shape* shp) {
	this->shp = shp;
	
	setPixelPos(pixelPos);
}

void Entity::setPixelPos(sf::Vector2f npos) {
	cx = (int) npos.x / Cst::CELL_SIZE;
	cy = (int) npos.y / Cst::CELL_SIZE;

	//getthe fractionnal part
	rx = fmodf((npos.x / Cst::CELL_SIZE), 1.0f);
	ry = fmodf((npos.y / Cst::CELL_SIZE), 1.0f);

	int here = 0;
	shp->setPosition(npos);
}

void Entity::setGridPos(sf::Vector2f npos) {
	setPixelPos(sf::Vector2f(npos.x * Cst::CELL_SIZE, npos.y * Cst::CELL_SIZE));
}

void Entity::im() {
	using namespace ImGui;
	DragFloat2("frict", &frictX, 0.01,0.5,1.0);
	DragInt2("cx", &cx);
	DragFloat2("rx", &rx);
	Value("pos x", shp->getPosition().x);
	Value("pos y", shp->getPosition().y);
}

void Entity::syncGridToPixel() {
	float pxX = (cx + rx) * Cst::CELL_SIZE;
	float pxY = (cy + ry) * Cst::CELL_SIZE;
	shp->setPosition(sf::Vector2f((int)pxX,(int)pxY));
}

void Entity::update() {
	rx += dx;
	ry += dy;

	dy += gravY;

	dx *= frictX;
	dy *= frictY;

	bool needSync = true;
	while( rx > 1){
		if( collides( cx+1, cy) ){
			rx = 0.99f;
			dx = 0;
		}
		else {
			rx--;
			cx++;//shall we collide before crossing cell bound ?
		}
	}
	while(rx < 0) {
		if (collides(cx-1, cy)) {
			rx = 0;
			dx = 0;
		}
		else {
			rx++;
			cx--;//shall we collide before crossing cell bound ?
		}
	}
	while (ry > 1) {
		if (collides(cx, cy+1)) {
			ry = 0.99f;
			dy = 0;
		}
		else {
			ry--;
			cy++;//shall we collide before crossing cell bound ?
		}
	}
	while (ry < 0) {
		bool testFeet = collides(cx, cy - 1);
		bool testBody = collides(cx, cy - 2);
		bool testHead = collides(cx, cy - 3);
		if (testFeet|| testBody || testHead) {
			ry = 0.0f;
			dy = 0;
		}
		else {
			ry++;
			cy--;//shall we collide before crossing cell bound ?
		}
	}
	if (needSync)
		syncGridToPixel();
}

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
}

bool Entity::collides(float gx, float gy) {
	return world.collides(gx, gy);
}
