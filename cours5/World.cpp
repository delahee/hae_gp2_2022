#include "World.hpp"
void World::update() {
	for(auto b : balls){
		if( !b->hooked ){
			int		nbColls = 0;
			Entity* collider = nullptr;

			auto bb = b->getGlobalBounds();
			for( auto c : statics){
				if(c->getGlobalBounds().intersects(bb)){
					collider = c;
					nbColls++;
					c->hit();
				}
			}

			if(nbColls>=2){
				b->setPosition(b->lastPos);
				b->speed.x = -b->speed.x;
				b->speed.y = -b->speed.y;
			}
			else if (nbColls >= 1) {
				Pad* isPad = dynamic_cast<Pad*>(collider);
				if(isPad)
				{
					if( b->getPosition().x < isPad->getPosition().x && (b->speed.x > 0))
						b->speed.x = -b->speed.x;
					else if (b->getPosition().x > isPad->getPosition().x && (b->speed.x < 0))
						b->speed.x = -b->speed.x;
					b->speed.y = -b->speed.y;
				}
				else 
				{
					auto sb = collider->getGlobalBounds();
					sf::FloatRect lineUp(sf::Vector2f(sb.left, sb.top), sf::Vector2f(sb.width, 1));
					sf::FloatRect lineDown(sf::Vector2f(sb.left, sb.top + sb.height), sf::Vector2f(sb.width, 1));
					sf::FloatRect lineLeft(sf::Vector2f(sb.left, sb.top), sf::Vector2f(1, sb.height));
					sf::FloatRect lineRight(sf::Vector2f(sb.left + sb.width, sb.top), sf::Vector2f(1, sb.height));

					if (bb.intersects(lineUp) || bb.intersects(lineDown))
						b->speed.y = -b->speed.y;

					if (bb.intersects(lineLeft) || bb.intersects(lineRight))
						b->speed.x = -b->speed.x;
				}
			}
			else {

			}
		}
	}
}
