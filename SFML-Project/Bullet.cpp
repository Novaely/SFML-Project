#include "Bullet.h"


Bullet::Bullet()
{
	stopFriction = 0.0f;
	turnBackFriction = 0.0f;
	acceleration = 0.0f;
	Desactive();
}

void Bullet::Active()
{
	speed = 500.0f;
}

void Bullet::Desactive()
{
	speed = 0;
	damage = 0;
}
