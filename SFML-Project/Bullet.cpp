#include "Bullet.h"

Bullet::Bullet() : Movable()
{
	characterType = CharaType::Bullet;
	shapeType = ShapeType::Circle;
	shape = new sf::CircleShape();

	((sf::CircleShape*)shape)->setRadius(5);
	broadRadius = 5;

	maxInputSpeed = 20;

	Desactive();
}

void Bullet::Active()
{
	Movable::Active();
	speed = 500.0f;

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
		isAlive = false;
		pDie(this);
	}
	else {
		const GameObject& Other = *(other);

		if (team == Team::Enemy)
		{
			if (Other.characterType == CharaType::Player)
			{
				//std::cout << "Enemy Bullet encountered Player (Destroy)" << std::endl;
				//isAlive = false;
				//pDie(this);
				Destroy();
			}
		}

		if (team == Team::Player)
		{
			if (Other.Color == _color)
			{
				if (Other.characterType == CharaType::CACEnemy)
				{
					//std::cout << "Player Bullet encountered CACEnemy (Destroy)" << std::endl;
					/*isAlive = false;
					pDie(this);*/
					Destroy();
				}
				if (Other.characterType == CharaType::ShooterEnemy)
				{
					//std::cout << "Player Bullet encountered ShooterEnemy (Destroy)" << std::endl;
					/*isAlive = false;
					pDie(this);*/
					Destroy();
				}
			}
		}
	}
}