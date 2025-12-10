#include "CACEnemy.h"

CACEnemy::CACEnemy() : Enemy()
{
	characterType = CharaType::CACEnemy;
	shapeType = ShapeType::Rectangle;
	shape = new sf::RectangleShape();
	shape->setFillColor(sf::Color::Red);

	((sf::RectangleShape*)shape)->setSize({ 5,5 });
	damage = 1.0f;

	maxInputSpeed = 150;
	acceleration = 400;
	stopFriction = 400;
	//turnBackFriction = 800;

	rotationSpeed = 100;
}

void CACEnemy::Active()
{
	Enemy::Active();
}

void CACEnemy::Desactive()
{
	Enemy::Active();
}

void CACEnemy::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	inputDirection = position.DirectionTo(*targetPos);
}

void CACEnemy::ChasePlayer(float deltaTime) {}

void CACEnemy::AttackPlayer() {}