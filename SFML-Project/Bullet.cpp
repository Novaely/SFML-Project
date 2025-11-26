#include "Bullet.h"


Bullet::Bullet() : Movable()
{
	shape = new sf::CircleShape();

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

void Bullet::Draw(sf::RenderWindow& window)
{
	shape->setPosition(position.x, position.y);

	shape->setFillColor(sf::Color::Red);
	((sf::CircleShape*)shape)->setRadius(5);
}