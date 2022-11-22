#pragma once

#include "Entities.hpp"

class World{
public:
	std::vector<Ball*>		balls;
	std::vector<Entity*>	statics;

	void update();
};