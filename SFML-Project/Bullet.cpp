#include "Bullet.h"

Bullet::Bullet() : Movable()
{
	shapeType = ShapeType::Circle;
	shape = new sf::CircleShape();

	sf::CircleShape* pShape = (sf::CircleShape*)shape;
	pShape->setRadius(5);
	pShape->setOrigin(5, 5);
	broadRadius = 5;

	Desactive();
}

void Bullet::Active()
{
	Movable::Active();
	speed = 225.0f;

	if (team == Team::Enemy)
	{
		layer = CollisionLayer::Layer_BulletEnemy;
		collisionMask = CollisionLayer::Layer_Player;
	}
	else
	{
		layer = CollisionLayer::Layer_BulletPlayer;
		collisionMask = CollisionLayer::Layer_Enemy;
	}
}

void Bullet::Desactive()
{
	Movable::Desactive();
	speed = 0;
	damage = 0;
}

void Bullet::OnCollisionEnter(GameObject* other)
{
	const GameObject& pOther = *(other);

	if (team == Team::Enemy && pOther.layer == Layer_Player)
	{
		Destroy();
		return;
	}

	if (team == Team::Player && pOther.layer == Layer_Enemy && pOther.Color == _color)
	{
		Destroy();
		return;
	}	
}