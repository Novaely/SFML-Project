#include "CACEnemy.h"

CACEnemy::CACEnemy() : Enemy()
{
	shape = new sf::RectangleShape();
	shape->setFillColor(sf::Color::Red);

	((sf::RectangleShape*)shape)->setSize({ 5,5 });
	detectionRadius = 150.0f;
	attackRadius = 50.0f;
	timeBetweenAttacks = 1.0f;
	attackTimer = 0.0f;
	damage = 10.0f;

	maxInputSpeed = 200;
	acceleration = 400;
	stopFriction = 400;
	turnBackFriction = 800;
	rotationSpeed = 100;
}

void CACEnemy::Active()
{
}

void CACEnemy::Desactive()
{
}

void CACEnemy::Update(float deltaTime)
{
	Enemy::Update(deltaTime);

	inputDirection = position.DirectionTo(*targetPos);
}

void CACEnemy::ChasePlayer(float deltaTime) {}

void CACEnemy::AttackPlayer() {}