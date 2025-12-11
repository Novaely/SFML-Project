#include "Collectible.h"

Collectible::Collectible() : GameObject() {
	_lifeTime = 5;
	shape = new sf::CircleShape();
	shapeType = ShapeType::Circle;
	
	layer = CollisionLayer::Collectible;
	collisionMask = static_cast<LayerMask>(CollisionLayer::Player);

	((sf::CircleShape*)shape)->setRadius(7.5f);
	broadRadius = 7.5f;
}

void Collectible::OnCollisionEnter(GameObject* other) 
{
	pCollected(this);
	Destroy();
}