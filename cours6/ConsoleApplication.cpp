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
#include "CmdFile.hpp"
#include "imgui.h"


using namespace sf;
struct Turtle{

	sf::Transform		trs;
	sf::CircleShape		eyes[2];
	sf::CircleShape		body;
	sf::VertexArray		traces;
	sf::Color			traceColor = sf::Color(0xff0000ff);

	bool				enableRecord = true;
	std::vector<Cmd>	rec;
	std::vector<Cmd>	replay;

	float				animSpeed = 1.0f;
	bool				isPenDown = false;

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
		if (enableRecord)
			rec.push_back({ onOff ? CmdId::PenDown : CmdId::PenUp, 0 });
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

		if (enableRecord)
			rec.push_back({ CmdId::Advance , pixels });
	}

	void turnLeft(float degrees = 10){
		trs = trs.rotate(-degrees);
		if(enableRecord)
			rec.push_back({ CmdId::RotateLeft , degrees });
	}

	void turnRight(float degrees = 10) {
		trs = trs.rotate(degrees);
		if (enableRecord)
			rec.push_back({ CmdId::RotateRight , degrees });
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
		animSpeed = 1.0f;
	}

	void replayCmd(Cmd&cmd){
		switch (cmd.id) {
		case CmdId::Advance:		advance(cmd.data); break;
		case CmdId::RotateLeft:		turnLeft(cmd.data); break;
		case CmdId::RotateRight:	turnRight(cmd.data); break;
		case CmdId::Reset:			reset(); break;
		case CmdId::PenDown:		setPenDown(true); break;
		case CmdId::PenUp:			setPenDown(false); break;
		case CmdId::Speed:			animSpeed = cmd.data; break;
		case CmdId::Color:			traceColor = sf::Color(cmd.data,cmd.data2,cmd.data3); break;
		default:
			break;
		}
	}

	bool replayCmdOne(Cmd& cmd) {
		int f = 2;
		float futureVal = f * animSpeed;
		if (cmd.data < futureVal) 
			futureVal = cmd.data;
		switch (cmd.id) {
		case CmdId::Advance:		advance(futureVal); break;
		case CmdId::RotateLeft:		turnLeft(futureVal); break;
		case CmdId::RotateRight:	turnRight(futureVal); break;
		case CmdId::Speed:			
			this->animSpeed = cmd.data; 
			cmd.data = 0; 
			break;
		case CmdId::Reset:			reset(); break;
		case CmdId::PenDown:		setPenDown(true); break;
		case CmdId::PenUp:			setPenDown(false); break;
		case CmdId::Color:			traceColor = sf::Color(cmd.data, cmd.data2, cmd.data3); cmd.data = 0; break;
		default:
			break;
		}
		cmd.data-= animSpeed * f;
		return cmd.data <= 0;
	}

	void updateReplay(){
		if( replay.size()){
			replayCmd(replay[0]);
			replay.erase(replay.begin());
		}
	}

	void updateReplayInterpolated(){
		if( replay.size()){
			bool isComplete = replayCmdOne(replay[0]);
			if(isComplete)
				replay.erase(replay.begin());
		}
	}

	void update(float dt) {
		updateEyes();

		if(enableRecord){

		}
		else if(replay.size()){
			//updateReplay();
			updateReplayInterpolated();
			// read cmd
			// apply delta of 1 only
			// substract from actual data 
			// of data reaches zero remove command
		}
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

	time_t lastModificationTime = {};
	double frameStart = 0;
	double frameEnd = 0.0015f;

	ImGui::SFML::Init(window);
	while (window.isOpen()) { // ONE FRAME
		double dt = frameEnd - frameStart;
		frameStart = Lib::getTimestamp();
		sf::Event event;

		bool doHotload = false;

		while (window.pollEvent(event)) { // ONE EVENT
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::Space){
					turtle.setPenDown(!turtle.isPenDown);
				}
				if (event.key.code == sf::Keyboard::R) {
					turtle.enableRecord = !turtle.enableRecord;
					printf("Recording %d\n", turtle.enableRecord);
				}
				if (event.key.code == sf::Keyboard::P) {
					turtle.replay = turtle.rec;
					printf("Replaying %d \n");
				}
				if (event.key.code == sf::Keyboard::K) {
					turtle.replay = { {CmdId::PenDown,100},{CmdId::Advance,100} };
				}

				if (event.key.code == sf::Keyboard::O) {
					turtle.replay =
					{
						{CmdId::PenDown,0},
						{CmdId::Advance,100},
						{CmdId::RotateLeft,90},
						{CmdId::Advance,100},
						{CmdId::RotateLeft,90},
						{CmdId::Advance,100},
						{CmdId::RotateLeft,90},
						{CmdId::Advance,100},
						{CmdId::RotateLeft,90},
					};
				}

				if (event.key.code == sf::Keyboard::S) {
					CmdFile::saveScript("save.txt", turtle.rec);
				}
				
				if (event.key.code == sf::Keyboard::L) {
					doHotload = true;
				}
			}
		}

		

		//if!hotload
		//sometime ask for mtime to do hotload on ourselves

		static int timer = 0;
		timer++;
		if( timer > 60){
			struct stat ts = {};
			stat("save.txt", &ts);
			if( ts.st_mtime > lastModificationTime )
				doHotload = true;
			timer = 0;
		}

		if( doHotload ){
			turtle.replay = CmdFile::loadScript("save.txt");
			turtle.enableRecord = false;
			struct stat ts = {};
			stat("save.txt", &ts);
			lastModificationTime = ts.st_mtime;
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
		
		turtle.update(dt);
		
		bool t = true;
		ImGui::SFML::Update(window, sf::Time( sf::seconds(dt)));
		{
			ImGui::ShowDemoWindow(&t);
		}
		window.clear();

		turtle.draw(window);

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