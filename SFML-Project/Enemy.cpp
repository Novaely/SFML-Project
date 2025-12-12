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
	const GameObject& pOther = *(other);

	if (pOther.layer == Layer_BulletPlayer && pOther.Color == _color)
	{
		Damage(10);
		return;
	}
}