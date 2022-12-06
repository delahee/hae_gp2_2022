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
#include "imgui.h"




using namespace sf;
class Player : public Entity {
public:
	Player() : Entity( sf::Vector2f(50,100) , new RectangleShape(sf::Vector2f(12,32)) ){
		auto rect  = (sf::RectangleShape*) this->shp;
		rect->setOrigin(6, 32);
		rect->setFillColor(sf::Color::Red);
		rect->setOutlineColor(sf::Color::Green);
		rect->setOutlineThickness(2);
	}
};


static Player * player = nullptr;

void testSFML(){
	player = new Player();
	std::cout << std::filesystem::current_path() << std::endl;

	sf::ContextSettings settings(0,0,2);
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	time_t lastModificationTime = {};
	double frameStart = 0;
	double frameEnd = 0.0015f;

	ImGui::SFML::Init(window);
	while (window.isOpen()) { // ONE FRAME
		double dt = frameEnd - frameStart;
		frameStart = Lib::getTimestamp();
		sf::Event event;

		while (window.pollEvent(event)) { // ONE EVENT
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::Space){
				}
				if (event.key.code == sf::Keyboard::R) {
				}
				if (event.key.code == sf::Keyboard::P) {
				}
				if (event.key.code == sf::Keyboard::K) {
				}

				if (event.key.code == sf::Keyboard::O) {
					
				}
				
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		}
		
		player->update();
		bool t = true;
		ImGui::SFML::Update(window, sf::Time( sf::seconds(dt)));
		{
			//ImGui::ShowDemoWindow(&t);

			ImGui::Begin("Debug", &t);

			player->im();

			ImGui::End();
		}
		window.clear();

		player->draw(window);

		ImGui::EndFrame();
		ImGui::SFML::Render(window);
		window.display();
		frameEnd = Lib::getTimestamp();
	}
	ImGui::SFML::Shutdown();
}

int WinMain() {
	testSFML();
	return 0;
}

int main(){
	testSFML();
	return 0;
}