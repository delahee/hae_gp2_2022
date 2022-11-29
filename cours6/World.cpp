#include "World.hpp"
void World::update() {
	updateCollision();
	updateDeleted();
}

void World::updateCollision() {
	
}

void World::updateDeleted(){
	for( auto b : toBeDeleted){
		auto& ws = statics;
		auto pos = std::find(ws.begin(), ws.end(), b);
		if (pos != ws.end())
			statics.erase(pos);
		delete b;
	}
	toBeDeleted.clear();
}
