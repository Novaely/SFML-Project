#include "Enemy.h"

Enemy::Enemy() : Character()
{
}


void Enemy::Active()
{
	health = 100.0f;
	speed = 100.0f;
	damage = 10.0f;

}

void Enemy::Desactive()
{
	health = 0.0f;
	speed = 0.0f;
	damage = 0.0f;

}
