#include "Bullet.h"


Bullet::Bullet() : Movable()
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

void Bullet::Draw(sf::RenderWindow& window)
{
	sf::CircleShape shape;
	shape.setPosition(position.x, position.y);

	shape.setFillColor(sf::Color::Red);
	shape.setRadius(5);

	window.draw(shape);
}