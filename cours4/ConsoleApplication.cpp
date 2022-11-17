#include "Lib.hpp"

#include <filesystem>
#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Catmull.hpp"
#include "Line.hpp"

static int GAME_WIDTH = 1600;
static int GAME_HEIGHT = 900;
static int GROUND_Y = 700;
static float SIGHT_TARGET = 0.5f;
static sf::RectangleShape ground(sf::Vector2f(GAME_WIDTH,2));
static sf::RectangleShape rect(sf::Vector2f(64,16));
static std::vector<sf::RectangleShape> catmullPoints;
static sf::VertexArray sight(sf::PrimitiveType::Lines);
static Line l;

struct Bullet {
	sf::CircleShape		shp;
	float				t = 0.0f;

	Bullet(){
		shp = sf::CircleShape(16);
		shp.setOrigin(16,16);
		shp.setFillColor(sf::Color(0xF29027ff));
		shp.setOutlineColor(sf::Color(0xF33313ff));
		shp.setOutlineThickness(2);
		t = 0.0f;
	}


	void update() {
		sf::Vector2f pos = l.interpolateCatmull(t);
		shp.setPosition(pos);
		t += 0.01;
	};
};

static std::vector<Bullet> bullets;

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

	auto plot = [&](sf::Vector2f p) {
		sf::RectangleShape p0(sf::Vector2f(16, 16));
		p0.setOrigin(8, 8);
		p0.setFillColor(sf::Color(0xF53C9DFF));
		p0.setOutlineColor(sf::Color::White);
		p0.setOutlineThickness(2);
		p0.setRotation(45);
		p0.setPosition(p);
		catmullPoints.push_back(p0);
	};

	plot(sf::Vector2f(100, 100));
	plot(sf::Vector2f(50, 200));
	plot(sf::Vector2f(200, 300));
	plot(sf::Vector2f(300, 300));
	plot(sf::Vector2f(0, 0));

	sf::RectangleShape& tPoint = catmullPoints.back();
	tPoint.setFillColor(sf::Color(0xC130FAff));

	std::vector<sf::Vector2f> p;

	while (window.isOpen()) { // ONE FRAME

		sf::Event event;
		while (window.pollEvent(event)) { // ONE EVENT
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyReleased){
				if(event.key.code == sf::Keyboard::Space)
					bullets.push_back(Bullet());
			}
		}

		float speed = 3.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			auto cannonPos = rect.getPosition();
			cannonPos.x-=speed;
			if (cannonPos.x < 0 )
				cannonPos.x = 0;
			rect.setPosition(cannonPos);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			auto cannonPos = rect.getPosition();
			cannonPos.x+=speed;
			if (cannonPos.x > GAME_WIDTH)
				cannonPos.x = GAME_WIDTH;
			rect.setPosition(cannonPos);

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			SIGHT_TARGET -= 0.01f;
			if (SIGHT_TARGET < 0)
				SIGHT_TARGET = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			SIGHT_TARGET += 0.01f;
			if (SIGHT_TARGET > 1)
				SIGHT_TARGET = 1;
		}
		p.clear();

		auto cannonPos = rect.getPosition();
		p.push_back( cannonPos );

		sf::Vector2f midPoint = sf::Vector2f(cannonPos.x * 0.5 + SIGHT_TARGET * GAME_WIDTH * 0.5f, GROUND_Y - 200);
		p.push_back(midPoint);
		p.push_back(sf::Vector2f(sf::Vector2f(SIGHT_TARGET * GAME_WIDTH, GROUND_Y)));
		l.setPoints(p);

		sf::Vector2f dir = midPoint - cannonPos;
		double len = sqrt(dir.x * dir.x + dir.y * dir.y);
		if(len>0){
			dir.x /= len;
			dir.y /= len;
		}
		double angle = atan2(dir.y, dir.x);
		double angleDeg = angle / (2.0 * 3.14159) * 360;
		CANNON_ROTATION = angleDeg;

		rect.setRotation(CANNON_ROTATION);

		auto cannonVtx = sf::Vertex(rect.getPosition());
		cannonVtx.color = sf::Color::Red;

		//draw sight
		sight.clear();
		sight.append(cannonVtx);

		sf::Transform t;
		auto tFinal = t.rotate(CANNON_ROTATION);
		auto dest = tFinal.transformPoint(sf::Vector2f(128,0));
		auto destVertex = sf::Vertex(dest);
		destVertex.position += cannonVtx.position;
		destVertex.color = sf::Color::Red;
		sight.append(destVertex);

		for (auto& b : bullets)
			b.update();
		//
		window.clear();
		window.draw(ground);
		window.draw(sight);
		window.draw(rect);

		for (auto& b : bullets)
			window.draw(b.shp);
		//l.draw(window);

		
		window.display();
	}
}

int main(){
	testSFML();
	return 0;
}