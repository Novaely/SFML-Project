#include "Bullet.h"

Bullet::Bullet() : Movable()
{
	characterType = CharaType::Bullet;
	shapeType = ShapeType::Circle;
	shape = new sf::CircleShape();

	((sf::CircleShape*)shape)->setRadius(5);
	broadRadius = 5;

	Desactive();
}

void Bullet::Active()
{
	Movable::Active();
	speed = 225.0f;

	if (team == Team::Enemy)
	{
		layer = CollisionLayer::BulletEnemy;
		collisionMask = static_cast<LayerMask>(CollisionLayer::Player);
	}
	else
	{
		layer = CollisionLayer::BulletPlayer;
		collisionMask = static_cast<LayerMask>(CollisionLayer::Enemy);
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