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
#include "CmdFile.hpp"
#include "World.hpp"
#include "imgui.h"


using namespace sf;
class Player : public Entity {
public:
	Player() : Entity( sf::Vector2f(50,100) , new RectangleShape(sf::Vector2f(24,64)) ){
		auto rect  = (sf::RectangleShape*) this->shp;
		rect->setOrigin(12, 64);
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

	auto bricks = CmdFile::loadScript("res/save.txt");
	for( auto & c : bricks)
		if (c.id == CmdId::Wall)
			world.statics.push_back(sf::Vector2i(c.x, c.y));
	world.mkGraphics();
	std::cout << "bricks read :" << std::to_string(bricks.size());
	
	while (window.isOpen()) { // ONE FRAME
		double dt = frameEnd - frameStart;
		frameStart = Lib::getTimestamp();
		sf::Event event;

		while (window.pollEvent(event)) { // ONE EVENT
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed){
				if (event.key.code == sf::Keyboard::Up
					|| event.key.code == sf::Keyboard::Space) {
					player->dy -= 2.0f;
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				int mcx = (int)event.mouseButton.x / Cst::CELL_SIZE;
				int mcy = (int)event.mouseButton.y / Cst::CELL_SIZE;
				//add block to world's statics
				//add test against statics in world
				world.poke(mcx, mcy);

				std::vector<Cmd> cmds;
				for(auto &s : world.statics)
					cmds.push_back({ CmdId::Wall,s.x,s.y });
				CmdFile::saveScript("res/save.txt",cmds);
			}
		}


		sf::Vector2f dir(0,0);
		float sp = 0.15f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			dir.x--;
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
			dir.x++;
		float len = sqrt(dir.x * dir.x + dir.y * dir.y);
		if( len ){
			dir.x /= len;
			dir.y /= len;
			player->dx += dir.x * sp;
			player->dy += dir.y * sp;
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
		world.draw(window);

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