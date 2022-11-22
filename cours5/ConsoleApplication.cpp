#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Catmull.hpp"
#include "Line.hpp"
#include "Entities.hpp"
#include "Game.hpp"


static Pad * pad = nullptr;
static Ball * ball = nullptr;
static int GROUND_Y = 700;
static float SIGHT_TARGET = 0.5f;
static sf::RectangleShape ground(sf::Vector2f(Game::WIDTH,2));

static int CANNON_ROTATION = -45;
void testSFML(){
	std::cout << std::filesystem::current_path() << std::endl;

	sf::ContextSettings settings(0,0,2);
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	
	ground.setPosition(0, GROUND_Y);
	ground.setFillColor(sf::Color(0x62F6D2ff));
	

	pad = new Pad(sf::Vector2f(Game::WIDTH * 0.5f, GROUND_Y));
	ball = new Ball(pad);
	
	while (window.isOpen()) { // ONE FRAME

		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased){
				
			}
		}

		float speed = 3.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			pad->moveLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			pad->moveRight();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {

		}
		
		ball->update();
	
		window.clear();

		window.draw(ground);
		pad->draw(window);
		ball->draw(window);
		window.display();
	}
}

int main(){
	testSFML();
	return 0;
}