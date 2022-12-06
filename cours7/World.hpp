#pragma once

#include "Entities.hpp"
#include "Part.hpp"

class World{
public:

	World();
	std::vector<Entity*>	statics;
	std::vector<Entity*>	toBeDeleted;

	void update();
	void updateCollision();
	void updateDeleted();
};
