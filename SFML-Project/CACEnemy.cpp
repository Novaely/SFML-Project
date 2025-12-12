#include "CACEnemy.h"

CACEnemy::CACEnemy() : Enemy()
{
	characterType = CharaType::CACEnemy;
	shapeType = ShapeType::Rectangle;
	shape = new sf::RectangleShape();
	shape->setFillColor(sf::Color::Red);

	sf::RectangleShape* pShape = (sf::RectangleShape*)shape;
	pShape->setSize({ 10,10 });

	damage = 1.0f;

	maxInputSpeed = 150;
	acceleration = 800;
	stopFriction = 400;
	turnBackFriction = 800;
	rotationSpeed = 100;

	Vec2f points[4] = { pShape->getPoint(0), pShape->getPoint(1) , pShape->getPoint(2), pShape->getPoint(3)};
	SetBroadRadiusFromPoints(points, 3);
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