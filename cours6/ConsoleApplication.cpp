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

using namespace sf;
struct Turtle{

	sf::Transform	trs;
	sf::CircleShape	eyes[2]; 
	sf::CircleShape	body; 
	sf::VertexArray traces;
	sf::Color		traceColor = sf::Color(0xff0000ff);

	bool			isPenDown = false;

	Turtle() {
		body = CircleShape(24);
		body.setOrigin(24,24);
		body.setFillColor(sf::Color(0x3DEB74ff));
		body.setOutlineColor(sf::Color(0xF54837ff));
		body.setOutlineThickness(2);

		body.setPosition(Game::WIDTH * 0.5f, Game::HEIGHT * 0.5f);
		trs.translate(body.getPosition());
		
		float eyeRadius = 6;
		for (auto& el  : eyes) {
			el.setRadius(eyeRadius);
			el.setOrigin(eyeRadius, eyeRadius);
			el.setFillColor(sf::Color(0xF73455ff));
			el.setOutlineColor(sf::Color(0x4A1019ff));
			el.setOutlineThickness(1);
		}

		traces.setPrimitiveType(sf::Lines);

		updateEyes();
	};

	void setPenDown(bool onOff) {
		isPenDown = onOff;
	};
	
	void setPenColor(sf::Color col) {
		traceColor = col;
	};

	void advance(float pixels = 10){
		auto pos = body.getPosition();

		trs = trs.translate(Vector2f(pixels,0));
		body.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));

		auto npos = body.getPosition();

		if( isPenDown ){
			traces.append(sf::Vertex(pos, traceColor));
			traces.append(sf::Vertex(npos, traceColor));
		}
	}

	void turnLeft(float degrees = 10){
		trs = trs.rotate(-degrees);
	}

	void turnRight(float degrees = 10) {
		trs = trs.rotate(degrees);
	}

	void updateEyes() {
		{
			auto el = trs;
			sf::Transform transed = el.translate(sf::Vector2f(24, 8));
			auto elCenter = transed.transformPoint(sf::Vector2f(0, 0));
			eyes[0].setPosition(elCenter);
		}
		{
			auto er = trs;
			sf::Transform transed = er.translate(sf::Vector2f(24, -8));
			auto erCenter = transed.transformPoint(sf::Vector2f(0, 0));
			eyes[1].setPosition(erCenter);
		}
	}

	void reset(){
		traces.clear();
		trs = sf::Transform();
		trs.translate(Game::WIDTH * 0.5f, Game::HEIGHT * 0.5f);
		body.setPosition(trs.transformPoint(sf::Vector2f(0, 0)));
		updateEyes();
	}

	void update(float dt) {
		updateEyes();
	};

	void draw(sf::RenderWindow& win) {
		win.draw(traces);
		win.draw(body);
		win.draw(eyes[0]);
		win.draw(eyes[1]);
	};
};

static Turtle turtle;

/*
* creer une class turtle ( derive de entity ? )
* elle a son objet graphique cercle + orientation 
* elle memorise son dessin dans ( vertex array ? )
* on l'update, on la draw
* ajouter commande advance( 1 px )
* ... compléter la classe
*/
void testSFML(){
	std::cout << std::filesystem::current_path() << std::endl;

	sf::ContextSettings settings(0,0,2);
	sf::RenderWindow window(sf::VideoMode(Game::WIDTH, Game::HEIGHT), "SFML works!");
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	double frameStart = 0;
	double frameEnd = 0.0015f;
	while (window.isOpen()) { // ONE FRAME
		frameStart = Lib::getTimestamp();
		double dt = frameEnd - frameStart;
		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::Space){
					turtle.setPenDown(!turtle.isPenDown);
				}
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			turtle.turnLeft();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
			turtle.reset();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			turtle.advance();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			turtle.turnRight();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			
		}
		turtle.update(dt);
		
		window.clear();

		turtle.draw(window);
		window.display();
		frameEnd = Lib::getTimestamp();
	}
}

int main(){
	testSFML();
	return 0;
}