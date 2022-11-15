#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Catmull.hpp"
#include "Line.hpp"

static int GAME_WIDTH = 720;
static int GAME_HEIGHT = 480;
static int GROUND_Y = 400;
static double catmullT = 0.5f;
static sf::RectangleShape ground(sf::Vector2f(GAME_WIDTH,2));
static sf::RectangleShape rect(sf::Vector2f(64,16));
static std::vector<sf::RectangleShape> catmullPoints;
static sf::VertexArray sight(sf::PrimitiveType::Lines);

static int CANNON_ROTATION = -45;
void testSFML(){
	std::cout << std::filesystem::current_path() << std::endl;

	sf::ContextSettings settings(0,0,2);
	sf::RenderWindow window(sf::VideoMode(GAME_WIDTH, GAME_HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	//rect.setFillColor(sf::Color::Red);
	rect.setOrigin(0, 8);
	rect.setPosition(GAME_WIDTH*0.5, GROUND_Y);
	rect.setRotation(CANNON_ROTATION);

	ground.setPosition(0, GROUND_Y);
	ground.setFillColor(sf::Color(0x62F6D2ff));
	
	sf::Texture texCannon;
	bool texOk = texCannon.loadFromFile("res/tex_cannon.png");
	if(!texOk){
		std::cout << " cannot load"<< "res/tex_cannon.png" << std::endl;
		return;
	}
	rect.setTexture(&texCannon, true);

	auto plot = [&](sf::Vector2f p) {
		sf::RectangleShape p0(sf::Vector2f(16, 16));
		p0.setOrigin(8, 8);
		p0.setFillColor(sf::Color(0xF53C9DFF));
		p0.setOutlineColor(sf::Color::White);
		p0.setOutlineThickness(2);
		p0.setRotation(45);
		p0.setPosition(p);
		catmullPoints.push_back(p0);
	};

	plot(sf::Vector2f(100, 100));
	plot(sf::Vector2f(50, 200));
	plot(sf::Vector2f(200, 300));
	plot(sf::Vector2f(300, 300));

	plot(sf::Vector2f(0, 0));

	sf::RectangleShape& tPoint = catmullPoints.back();
	tPoint.setFillColor(sf::Color(0xC130FAff));

	while (window.isOpen()) { // ONE FRAME

		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/*
		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			CANNON_ROTATION--;
			rect.setRotation(CANNON_ROTATION);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			CANNON_ROTATION++;
			rect.setRotation(CANNON_ROTATION);
		}*/


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			catmullT -= 0.01f;
			if (catmullT < 0)
				catmullT = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			catmullT += 0.01f;
			if (catmullT > 1)
				catmullT = 1;
		}

		auto cannonPos = sf::Vertex(rect.getPosition());
		cannonPos.color = sf::Color::Red;

		//draw sight
		sight.clear();
		sight.append(cannonPos);

		sf::Transform t;
		auto tFinal = t.rotate(CANNON_ROTATION);
		auto dest = tFinal.transformPoint(sf::Vector2f(128,0));
		auto destVertex = sf::Vertex(dest);
		destVertex.position += cannonPos.position;
		destVertex.color = sf::Color::Red;
		sight.append(destVertex);

		sf::Vector2f calc = Catmull::polynom2( 
			catmullPoints[0].getPosition(),
			catmullPoints[1].getPosition(),
			catmullPoints[2].getPosition(),
			catmullPoints[3].getPosition(),catmullT);
		tPoint.setPosition(calc);

		//
		window.clear();
		window.draw(ground);
		window.draw(sight);
		window.draw(rect);

		for( auto& cp : catmullPoints)
			window.draw(cp);
		
		window.display();
	}
}

int main(){
	testSFML();
	return 0;
}