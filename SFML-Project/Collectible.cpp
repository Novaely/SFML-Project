#include "Collectible.h"

Collectible::Collectible() : GameObject() {
	shape = new sf::CircleShape();
	shapeType = ShapeType::Circle;
	sf::CircleShape* pShape = (sf::CircleShape*)shape;
	pShape->setPointCount(5);
	pShape->setRadius(7.5f);
	pShape->setOrigin(7.5f, 7.5f);
	broadRadius = 7.5f;
	
	layer = CollisionLayer::Layer_Collectible;
	collisionMask = CollisionLayer::Layer_Player;
}

void Collectible::OnCollisionEnter(GameObject* other) 
{
	pCollected(this);
	Destroy();
}