#include "Enemy.h"

class Player;

Enemy::Enemy() : Character()
{
	layer = CollisionLayer::Enemy;
	collisionMask = static_cast<LayerMask>(CollisionLayer::BulletPlayer) |
		static_cast<LayerMask>(CollisionLayer::Player);
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
