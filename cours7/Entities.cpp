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

}

void Entity::syncGridToPixel() {
	float pxX = (cx + rx) * Cst::CELL_SIZE;
	float pxY = (cy + ry) * Cst::CELL_SIZE;
	shp->setPosition(sf::Vector2f(pxX,pxY));
}

void Entity::update() {

}

void Entity::draw(sf::RenderWindow& win) {
	win.draw(*shp);
}
