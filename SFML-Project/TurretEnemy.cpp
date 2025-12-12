#include "TurretEnemy.h"

TurretEnemy::TurretEnemy() : ShooterEnemy()
{
	sf::ConvexShape* pShape = (sf::ConvexShape*)shape;
	pShape->setPoint(0, sf::Vector2f{ 4, 0 });
	pShape->setPoint(1, sf::Vector2f{ -15, 15 });
	pShape->setPoint(2, sf::Vector2f{ -15, -15 });
	bulletSpawnPos = CustomVector2f(4, 0);

	Vec2f points[3] = { pShape->getPoint(0), pShape->getPoint(1) , pShape->getPoint(2) };
	SetBroadRadiusFromPoints(points, 3);

	maxInputSpeed = 0.0f;

	timerShootAgain = 5.f;
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

void TurretEnemy::Damage(float dmg)
{
	ShooterEnemy::Damage(dmg);

	if (!isAlive && lastLightningShooted != nullptr && lastLightningShooted->isAlive)
	{
		lastLightningShooted->StopLightning();
		lastLightningShooted = nullptr;
	}
}