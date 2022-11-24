#pragma once

#include "Entities.hpp"
#include "Part.hpp"

class World{
public:
	std::vector<Ball*>		balls;
	std::vector<Entity*>	statics;

	std::vector<Entity*>	toBeDeleted;

	void update();
	void updateCollision();
	void updateDeleted();
};

extern World world;
extern PartController particles;