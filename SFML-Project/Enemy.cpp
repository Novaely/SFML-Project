#include "Enemy.h"


Player;
GameManager;

Enemy::Enemy() : Character()
{
}


void Enemy::Active()
{
}

void Enemy::Desactive()
{
}

void Enemy::OnCollisionEnter(GameObject* other)
{
	GameObject Other = *(other);

	if (Other.Color == _color)
	{
		if (Other.characterType == CharaType::Bullet)
		{
			if (Other.team == Team::Player)
			{
				std::cout << "Enemy hit by bullet" << std::endl;
			}
		}
	}

}
