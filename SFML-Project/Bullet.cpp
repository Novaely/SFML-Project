#include "Bullet.h"

Bullet::Bullet() : Movable()
{
	characterType = CharaType::Bullet;
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
	if (other == nullptr) {
		Destroy();
	}
	else {
		const GameObject& Other = *(other);

		if (team == Team::Enemy)
		{
			if (Other.characterType == CharaType::Player)
			{
				Destroy();
			}
		}

		if (team == Team::Player)
		{
			if (Other.Color == _color)
			{
				if (Other.characterType == CharaType::CACEnemy)
				{
					Destroy();
				}
				if (Other.characterType == CharaType::ShooterEnemy)
				{
					Destroy();
				}
			}
		}
	}
}