#include "TurretEnemy.h"

TurretEnemy::TurretEnemy() : ShooterEnemy()
{
	sf::ConvexShape* pShape = (sf::ConvexShape*)shape;

	pShape->setPoint(0, sf::Vector2f{ 4, 0 });
	pShape->setPoint(1, sf::Vector2f{ -15, 15 });
	pShape->setPoint(2, sf::Vector2f{ -15, -15 });
	bulletSpawnPos = CustomVector2f(4, 0);

	maxInputSpeed = 0.0f;

	timerShootAgain = 5.0f;
	chronoShootAgain = timerShootAgain;
}

void TurretEnemy::TryShoot()
{
	if (chronoShootAgain >= timerShootAgain)
	{
		chronoShootAgain = 0;
		_canShoot = false;
		OnShoot(*this);
	}
}