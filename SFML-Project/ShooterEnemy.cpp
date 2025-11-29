#include "ShooterEnemy.h"

ShooterEnemy::ShooterEnemy() {
	Color = ColorType::Rouge;
	shape = new sf::ConvexShape();
	shape->setFillColor(_colors[_color]);
	sf::ConvexShape* pShape = (sf::ConvexShape*)shape;

	pShape->setOrigin(0, 0);
	pShape->setPointCount(3);
	pShape->setPoint(0, sf::Vector2f{ 2, 0 });
	pShape->setPoint(1, sf::Vector2f{ -7.5f, 7.5f });
	pShape->setPoint(2, sf::Vector2f{ -7.5f, -7.5f });
	bulletSpawnPos = CustomVector2f(10, 0);

	maxInputSpeed = 100;
	acceleration = 400;
	stopFriction = 400;
	//turnBackFriction = 800;
	rotationSpeed = 100;

	attackRadius = 100;
	timerShootAgain = 2.0f;
	speedBullet = 150;
	chronoShootAgain = timerShootAgain;
}

void ShooterEnemy::Update(float deltaTime)
{
	rotation = Math::ToDegree(position.AngleTo(*targetPos));

	inputDirection = position.DirectionTo(*targetPos);

	if (position.DistanceTo(*targetPos) <= attackRadius)
	{
		inputDirection = Math::RotatePoint(inputDirection, CustomVector2f::zero, Math::PI * 0.5);
	}

	Enemy::Update(deltaTime);

	TryShoot();
}

void ShooterEnemy::TryShoot()
{
	if (chronoShootAgain >= timerShootAgain)
	{
		chronoShootAgain = 0;
		_canShoot = false;
		OnShoot(*this);
	}
}