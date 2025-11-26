#include "Bullet.h"


Bullet::Bullet() : Movable()
{
	shape = new sf::CircleShape();
	shape->setFillColor(sf::Color::Red);

	((sf::CircleShape*)shape)->setRadius(5);

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