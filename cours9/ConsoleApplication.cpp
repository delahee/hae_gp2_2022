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
#include <unordered_map>
#include <algorithm>
#include "Dijkstra.hpp"


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

/*
namespace std {
	template <> struct hash<sf::Vector2i> {
		std::size_t operator()(const sf::Vector2i& k) const {
			using std::hash;
			return std::size_t((k.y << 16) | k.x);
		}
	};
}*/


static Vector2i			arrival;
static RectangleShape	arrivalShape;
static Dijkstra dij;
static Player * player = nullptr;
static sf::VertexArray points;
static sf::VertexArray lines;
static sf::VertexArray path;

void printGraph(BaseGraph& g, sf::VertexArray & points) {
	int hcell = Cst::CELL_SIZE >> 1;
	points.clear();
	for (auto& p : g) {
		points.append(sf::Vertex(sf::Vector2f(p.first.x * Cst::CELL_SIZE + hcell, p.first.y * Cst::CELL_SIZE + hcell), sf::Color::Red));
	}
};

void printDij(Dijkstra& g, sf::VertexArray& lines) {
	int hcell = Cst::CELL_SIZE >> 1;
	lines.clear();

	sf::Color col = sf::Color(180, 0, 255, 200);
	for(auto & p :dij.pred){
		auto& from = p.first;
		auto& to = p.second;
		lines.append(sf::Vertex(sf::Vector2f(from.x * Cst::CELL_SIZE + hcell, from.y * Cst::CELL_SIZE + hcell), col));
		lines.append(sf::Vertex(sf::Vector2f(to.x * Cst::CELL_SIZE + hcell, to.y * Cst::CELL_SIZE + hcell), col));
	}
}

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

	points.setPrimitiveType(Points);
	lines.setPrimitiveType(Lines);

	arrivalShape.setOutlineColor(sf::Color::Magenta);
	arrivalShape.setFillColor(sf::Color::Green);
	arrivalShape.setOutlineThickness(2);
	arrivalShape.setSize(sf::Vector2f(6, 6));
	arrivalShape.setOrigin(arrivalShape.getSize().x*0.5, arrivalShape.getSize().y * 0.5);



	

	auto bricks = CmdFile::loadScript("res/save.txt");
	for( auto & c : bricks)
		if (c.id == CmdId::Wall)
			world.statics.push_back(sf::Vector2i(c.x, c.y));
	world.mkGraphics();
	std::cout << "bricks read :" << std::to_string(bricks.size());
	
	bool refreshPath = true;
	while (window.isOpen()) { // ONE FRAME
		double dt = frameEnd - frameStart;
		frameStart = Lib::getTimestamp();
		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			
			ImGui::SFML::ProcessEvent(window, event);
			player->onEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
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

			if (event.type == sf::Event::KeyReleased) {

				if (event.key.code == sf::Keyboard::C) {
					std::unordered_map<sf::Vector2i, bool> g;
					dij.setGraph( g );
				}
				if( event.key.code == sf::Keyboard::G){
					//creer un graph de toute les cases valides

					//std::vector<> g <- contient toutes les cases (cx,cy) valides de notre jeu
					//std::unordered_map<> g <- contient toutes les cases (cx,cy) valides de notre jeu

					// le passer a "quelque chose" qui sera notre futur dijkstra
					//appeler afficher graph( g )
					
					std::unordered_map<sf::Vector2i, bool> g;
					for(int y = 0; y <  1 + (Game::HEIGHT / Cst::CELL_SIZE); ++y)
						for (int x = 0; x < 1 + (Game::WIDTH / Cst::CELL_SIZE); ++x) {
							if (!world.collides(x, y))
								g[sf::Vector2i(x, y)] = true;
						}
					dij.setGraph(g);
					dij.build(sf::Vector2i(player->cx, player->cy));
					printGraph(g, points);
					printDij(dij, lines);
					refreshPath = true;
				}

				
			}
		}
		
		player->update();
		bool t = true;
		ImGui::SFML::Update(window, sf::Time( sf::seconds(dt)));
		{
			using namespace ImGui;
			//ImGui::ShowDemoWindow(&t);

			ImGui::Begin("Debug", &t);

			player->im();

			if (DragInt2("arrival", &arrival.x)) {
				arrivalShape.setPosition(sf::Vector2f(arrival.x * Cst::CELL_SIZE + Cst::CELL_SIZE * 0.5, arrival.y * Cst::CELL_SIZE + Cst::CELL_SIZE * 0.5));
				refreshPath = true;
			}
	
			if( TreeNode("dijkstra")){
				dij.im();
				TreePop();
			}

			if(Button("Follow Path")){

				player->curPath = dij.getPath(arrival);
				std::reverse(player->curPath.begin(), player->curPath.end());
				player->changeState(player->pathState);
			}

			ImGui::End();
		}

		if (refreshPath) {
			auto pathToArrival = dij.getPath(arrival);
			
			path.setPrimitiveType(LineStrip);
			path.clear();
			for(auto & vtx: pathToArrival)
				path.append(sf::Vertex(sf::Vector2f(vtx.x*Cst::CELL_SIZE + Cst::CELL_SIZE*0.5f, vtx.y * Cst::CELL_SIZE + Cst::CELL_SIZE * 0.5f),sf::Color::Blue));
			refreshPath = false;
		}
		window.clear();
		
		player->draw(window);
		world.draw(window);
		window.draw(points);
		window.draw(lines);
		window.draw(arrivalShape);
		window.draw(path);

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