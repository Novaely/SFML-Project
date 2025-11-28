#include "Bullet.h"


Bullet::Bullet() : Movable()
{
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
	const GameObject& Other = *(other);

	if (team == Team::Enemy)
	{
		if (Other.characterType == CharaType::Player)
		{
			std::cout << "Enemy Bullet encountered Player (Destroy)" << std::endl;
		}
	}

	if (team == Team::Player)
	{
		if (Other.Color == _color)
		{
			if (Other.characterType == CharaType::CACEnemy)
			{
				std::cout << "Player Bullet encountered CACEnemy (Destroy)" << std::endl;
			}
			if (Other.characterType == CharaType::ShooterEnemy)
			{
				std::cout << "Player Bullet encountered ShooterEnemy (Destroy)" << std::endl;
			}
		}
	}

	// si bullet sort de l'ecran -> Destroy

}