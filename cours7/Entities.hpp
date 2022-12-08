#pragma once

#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

#include "Cst.hpp"

class Entity{
public:
	sf::Shape*		shp = nullptr;

	float			rx = 0.5f;//
	float			ry = 1.0f;

	float			dx = 0.0f;
	float			dy = 0.0f;

	float			frictX = 0.91f;
	float			frictY = 0.96f;

	float			gravY = 0.1f;

	int				cx = 0;
	int				cy = 0;

	Entity(sf::Vector2f pixelPos, sf::Shape* shp);

	void setPixelPos(sf::Vector2f npos);
	void setGridPos(sf::Vector2f npos);

	void im();

	inline auto getLocalBounds() const {
		return shp->getLocalBounds();
	};
	
	inline auto getGlobalBounds() const {
		return shp->getGlobalBounds();
	};
	inline auto getPosition() const {
		return shp->getPosition();
	};
	
	inline void setPosition(const sf::Vector2f& v) {
		shp->setPosition(v);
	};
	
	void syncGridToPixel();
	void update();
	void draw(sf::RenderWindow& win);
	bool collides(float gx,float gy);
};
