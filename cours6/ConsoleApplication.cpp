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
#include "Part.hpp"
#include "World.hpp"



void testSFML(){
	std::cout << std::filesystem::current_path() << std::endl;

	sf::ContextSettings settings(0,0,2);
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	

	while (window.isOpen()) { // ONE FRAME

		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased){
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		}
		
		window.clear();
		window.display();

	}
}

int main(){
	testSFML();
	return 0;
}