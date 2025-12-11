#include "Collectible.h"

Collectible::Collectible() : GameObject() {
	_lifeTime = 5;
	shape = new sf::CircleShape();
	shapeType = ShapeType::Circle;
	
	layer = CollisionLayer::Layer_Collectible;
	collisionMask = CollisionLayer::Layer_Player;

	sf::CircleShape* pShape = (sf::CircleShape*)shape;
	pShape->setRadius(7.5f);
	pShape->setOrigin(7.5f, 7.5f);
	broadRadius = 7.5f;
}

void Collectible::OnCollisionEnter(GameObject* other) 
{
	pCollected(this);
	Destroy();
}