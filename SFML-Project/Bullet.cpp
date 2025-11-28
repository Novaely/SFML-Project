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