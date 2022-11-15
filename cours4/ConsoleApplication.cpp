#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Catmull.hpp"

static int GAME_WIDTH = 720;
static int GAME_HEIGHT = 480;
static int GROUND_Y = 400;
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

	while (window.isOpen()) { // ONE FRAME

		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
			CANNON_ROTATION--;
			rect.setRotation(CANNON_ROTATION);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			CANNON_ROTATION++;
			rect.setRotation(CANNON_ROTATION);
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