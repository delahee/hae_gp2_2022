#include "Game.hpp"
#include "World.hpp"

World world;

World::World(){

}

bool World::collides(float gx, float gy) {
	if( gx > Game::WIDTH / Cst::CELL_SIZE)
		return true;
	if (gy > ((Game::HEIGHT / Cst::CELL_SIZE)-3))
		return true;
	else if (gx < 0) 
		return true;
	else if (gy < 0)
		return true;
	return false;
}
