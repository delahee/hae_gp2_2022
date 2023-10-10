#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <algorithm>

#include "imgui.h"
#include "Game.hpp"

using namespace sf;


static sf::RectangleShape	charSprite;
static sf::Texture			chars;
static sf::Shader			shader;
static sf::Shader			frag;
static sf::Glsl::Vec4		uColorMul(1,1,1,1);
static sf::Glsl::Vec4		uColorAdd(0,0,0,0);
static sf::Glsl::Mat4		uColorTransform = sf::Glsl::Mat4(sf::Transform());

void testSFML(){
	std::cout << std::filesystem::current_path() << std::endl;

	sf::ContextSettings settings(0,0,2);
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	time_t lastModificationTime = {};
	double frameStart = 0;
	double frameEnd = 0.0015f;

	{
		bool loaded = chars.loadFromFile("res/character_arts.png");
		if (!loaded)
			printf("img not loaded");
		else
			chars.setSmooth(true);
	}

	{
		bool loaded = shader.loadFromFile("res/main.vsh","res/main.fsh");
		if (!loaded)
			printf("shader not loaded");

		shader.setUniform("uColorMul", uColorMul);
		shader.setUniform("uColorAdd", uColorAdd);
		shader.setUniform("uColorTransform", uColorTransform);
	}

	{
		charSprite.setPosition(20, 20);
		charSprite.setTexture(&chars);
		charSprite.setSize( sf::Vector2f( 1024, 1024));
	}


	ImGui::SFML::Init(window);

	bool refreshPath = true;
	while (window.isOpen()) { // ONE FRAME
		double dt = frameEnd - frameStart;
		frameStart = Lib::getTimestamp();
		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			
			ImGui::SFML::ProcessEvent(window, event);
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed) {
				
			}

			if (event.type == sf::Event::KeyReleased) {

				if (event.key.code == sf::Keyboard::C) {
				}
				if( event.key.code == sf::Keyboard::G){

				}
			}
		}
		
		bool t = true;
		ImGui::SFML::Update(window, sf::Time( sf::seconds(dt)));
		{
			using namespace ImGui;
			ImGui::Begin("Debug", &t);
			ImGui::Text("toto");
			if( ImGui::ColorEdit4("Color Add", &uColorAdd.x) )
				shader.setUniform("uColorAdd", uColorAdd);
			if( ImGui::ColorEdit4("Color Mul", &uColorMul.x) )
				shader.setUniform("uColorMul", uColorMul);

			bool matrixUpdated = false;
			if (ImGui::ColorEdit4("Color R", &uColorTransform.array[0]))
				matrixUpdated = true;
			if (ImGui::ColorEdit4("Color G", &uColorTransform.array[4]))
				matrixUpdated = true;
			if (ImGui::ColorEdit4("Color B", &uColorTransform.array[8]))
				matrixUpdated = true;
			if (ImGui::ColorEdit4("Color Alpha", &uColorTransform.array[12]))
				matrixUpdated = true;

			if( Button("set grayscale")){
				float gs[16] = {
					0.3, 0.3, 0.3, 0,
					0.59, 0.59, 0.59, 0,
					0.11, 0.11, 0.11, 0,
					  0,    0,    0, 1, };
				memcpy(uColorTransform.array,gs, 16*sizeof(float));
				matrixUpdated = true;
			}

			if( matrixUpdated)
				shader.setUniform("uColorTransform", uColorTransform);
			ImGui::End();
		}


		window.clear();
		sf::RenderStates rs;
		rs.shader = &shader;
		window.draw(charSprite,rs);

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