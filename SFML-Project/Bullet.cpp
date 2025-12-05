#include "Bullet.h"

Bullet::Bullet() : Movable()
{
	characterType = CharaType::Bullet;
	shape = new sf::CircleShape();

	((sf::CircleShape*)shape)->setRadius(5);
	maxInputSpeed = 20;

	Desactive();
}

void Bullet::Active()
{
	Movable::Active();
	speed = 500.0f;
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
			pDie(this);
	}
	else {
		const GameObject& Other = *(other);

		if (team == Team::Enemy)
		{
			if (Other.characterType == CharaType::Player)
			{
				std::cout << "Enemy Bullet encountered Player (Destroy)" << std::endl;
				pDie(this);
			}
		}

		if (team == Team::Player)
		{
			if (Other.Color == _color)
			{
				if (Other.characterType == CharaType::CACEnemy)
				{
					std::cout << "Player Bullet encountered CACEnemy (Destroy)" << std::endl;
					pDie(this);
				}
				if (Other.characterType == CharaType::ShooterEnemy)
				{
					std::cout << "Player Bullet encountered ShooterEnemy (Destroy)" << std::endl;
					pDie(this);
				}
			}
		}
	}
}