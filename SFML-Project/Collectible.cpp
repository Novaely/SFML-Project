#include "Collectible.h"

Collectible::Collectible() : GameObject() {
	_lifeTime = 5;
	shape = new sf::CircleShape();

	((sf::CircleShape*)shape)->setRadius(5);
}