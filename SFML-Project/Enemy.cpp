#include "Enemy.h"

class Player;

Enemy::Enemy() : Character()
{
	layer = CollisionLayer::Layer_Enemy;
	collisionMask = CollisionLayer::Layer_BulletPlayer | CollisionLayer::Layer_Player;
}


void Enemy::Active()
{
	Character::Active();
}

void Enemy::Desactive()
{
	Character::Active();
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
