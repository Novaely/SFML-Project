#include "Collectible.h"

Collectible::Collectible() : GameObject() {
	_lifeTime = 5;
	shape = new sf::CircleShape();
	shapeType = ShapeType::Circle;
	
	layer = CollisionLayer::Collectible;
	collisionMask = static_cast<LayerMask>(CollisionLayer::Player);

	((sf::CircleShape*)shape)->setRadius(5);
	broadRadius = 5;
}

void Collectible::OnCollisionEnter(GameObject* other) {


	pCollected(this);
	this->isAlive = false;
	pDie(this);
}