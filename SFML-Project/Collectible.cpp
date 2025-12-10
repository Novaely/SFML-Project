#include "Collectible.h"

Collectible::Collectible() : GameObject() {
	_lifeTime = 5;
	shape = new sf::CircleShape();
	shapeType = ShapeType::Circle;

	((sf::CircleShape*)shape)->setRadius(5);
}

void Collectible::OnCollisionEnter(GameObject* other) {


	pCollected(this);
	this->isAlive = false;
	pDie(this);
}