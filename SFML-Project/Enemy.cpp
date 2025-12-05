#include "Enemy.h"


class Player;

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
	const GameObject& Other = *(other);

	if (Other.team == Team::Player)
	{
		if (Other.characterType == CharaType::Bullet)
		{
			if (Other.Color == _color)
			{
				Damage(10);
			}
		}
	}

}
