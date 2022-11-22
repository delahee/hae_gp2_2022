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
#include "World.hpp"


static World world;
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

	world.balls.push_back(ball);

	world.statics.push_back(pad);

	auto wl = new Wall(sf::FloatRect(sf::Vector2f(-2, 0), sf::Vector2f(4, Game::HEIGHT)));
	world.statics.push_back(wl); 
	
	auto wr = new Wall(sf::FloatRect(sf::Vector2f(-2 + Game::WIDTH, 0), sf::Vector2f(4, Game::HEIGHT)));
	world.statics.push_back(wr);

	auto wt = new Wall(sf::FloatRect( sf::Vector2f(-2 , -2), sf::Vector2f(Game::WIDTH + 4, 4)));
	world.statics.push_back(wt);

	auto br0 = new Brick( sf::FloatRect( sf::Vector2f(50,50), sf::Vector2f(32,8)));
	world.statics.push_back(br0);
	
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			auto pad = ball->hooked;
			if (pad) {
				ball->hooked = nullptr;
				auto dir = ball->getPosition() - pad->getPosition();
				Lib::safeNormalize(dir);
				float sp = 15.0f;
				dir.x *= sp;
				dir.y *= sp;
				ball->speed = dir;
			}
		}
		
		ball->update();
		world.update();
	
		window.clear();

		window.draw(ground);

		for (auto st : world.statics)
			st->draw(window);

		pad->draw(window);
		
		ball->draw(window);
		window.display();

		if (ball->getPosition().y > Game::HEIGHT) {
			ball->initPos(pad);
		}
	}
}

int main(){
	testSFML();
	return 0;
}