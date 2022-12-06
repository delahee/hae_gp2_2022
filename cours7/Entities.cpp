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
	Value("cx", cx);
	Value("cy", cy);
	Value("rx", rx);
	Value("ry", ry);
	Value("pos x", shp->getPosition().x);
	Value("pos y", shp->getPosition().y);

	if( Button("advance 1 cell") ){
		cy--;
		syncGridToPixel();
	}
	if (Button("back 1 cell")) {
		cy++;
		syncGridToPixel();
	}
	if (Button("left 1 cell")) {
		cx--;
		syncGridToPixel();
	}

	if (Button("right 1 cell")) {
		cx++;
		syncGridToPixel();
	}

	float nudge = 0.1f;
	if (Button("advance 1 nudge")) {
		ry-=nudge;
	}
	if (Button("back 1 nudge")) {
		ry+= nudge;
	}
	if (Button("left 1 nudge")) {
		rx-= nudge;
	}
	if (Button("right 1 nudge")) {
		rx+= nudge;
	}

}

void Entity::syncGridToPixel() {
	float pxX = (cx + rx) * Cst::CELL_SIZE;
	float pxY = (cy + ry) * Cst::CELL_SIZE;
	shp->setPosition(sf::Vector2f((int)pxX,(int)pxY));
}

void Entity::update() {
	bool needSync = true;
	while( rx > 1){
		rx--;
		cx++;//shall we collide before crossing cell bound ?
	}
	while(rx < 0) {
		rx++;
		cx--;//shall we collide before crossing cell bound ?
	}
	while (ry > 1) {
		ry--;
		cy++;//shall we collide before crossing cell bound ?
	}
	while (ry < 0) {
		ry++;
		cy--;//shall we collide before crossing cell bound ?
	}
	if (needSync)
		syncGridToPixel();
}

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
}
