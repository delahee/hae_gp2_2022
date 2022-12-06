#pragma once

#include "Entities.hpp"
#include "Part.hpp"

class World{
public:
	World();
	std::vector<sf::Vector2i>	statics;
	bool collides(float gx, float gy);
};

extern World world;
