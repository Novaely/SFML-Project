#include "PoolManager.h"

PoolManager::PoolManager()
	: bulletPool(startNumBullets, nullptr), cacEnemyPool(startNumCACEnemy, nullptr),
	shooterEnemyPool(startNumShooterEnemy, nullptr)
{
	for (int i = 0; i < startNumBullets; i++)
	{
		bulletPool[i] = new Bullet();
	}
	currentNumBullets = startNumBullets;

	for (int i = 0; i < startNumCACEnemy; i++)
	{
		cacEnemyPool[i] = new CACEnemy();
	}
	currentNumCACEnemy = startNumCACEnemy;

	for (int i = 0; i < startNumShooterEnemy; i++)
	{
		shooterEnemyPool[i] = new ShooterEnemy();
	}
	currentNumShooterEnemy = startNumShooterEnemy;
}

#pragma region Bullets

Bullet* PoolManager::ExtractBullet()
{
	if (indexOfFirstBullet >= currentNumBullets)
	{
		AddBulletInPool();
	}

	Bullet* pBullet = bulletPool[indexOfFirstBullet];

	bulletPool[indexOfFirstBullet] = nullptr;

	indexOfFirstBullet++;

	return pBullet;
}

Bullet* PoolManager::GetBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage)
{
	Bullet* pBullet = ExtractBullet();

	pBullet->team = team;
	pBullet->position = position;
	pBullet->speed = CustomVector2f(speed);
	pBullet->maxInputSpeed = speed;
	pBullet->moveDirection = direction;
	pBullet->damage = damage;

	pBullet->Active();

	return pBullet;
}

void PoolManager::AddBulletInPool()
{
	currentNumBullets += 10;

	bulletPool.resize(currentNumBullets, nullptr);

	for (int i = indexOfFirstBullet; i < currentNumBullets; i++)
	{
		bulletPool[i] = new Bullet();
	}
}

void PoolManager::ReturnBullet(Bullet* bullet)
{
	bullet->Desactive();

	indexOfFirstBullet--;

	bulletPool[indexOfFirstBullet] = bullet;
}

#pragma endregion

#pragma region CACEnemy

CACEnemy* PoolManager::ExtractCACEnemy()
{
	if (indexOfFirstCACEnemy >= currentNumCACEnemy) AddCACEnemyInPool();

	CACEnemy* pEnemy = cacEnemyPool[indexOfFirstCACEnemy];

	cacEnemyPool[indexOfFirstCACEnemy] = nullptr;
	indexOfFirstCACEnemy++;

	return pEnemy;
}

CACEnemy* PoolManager::GetCACEnemy(CustomVector2f position, float health, Player* player)
{
	CACEnemy* pEnemy = ExtractCACEnemy();

	pEnemy->team = Team::Enemy;
	pEnemy->position = position;
	pEnemy->health;
	// TO DO : Give player

	pEnemy->Active();

	return pEnemy;
}

void PoolManager::AddCACEnemyInPool()
{
	currentNumCACEnemy += 10;

	cacEnemyPool.resize(currentNumCACEnemy,nullptr);

	for (int i = indexOfFirstCACEnemy; i < currentNumCACEnemy; i++)
	{
		cacEnemyPool[i] = new CACEnemy();
	}
}

void PoolManager::ReturnEnemy(CACEnemy* enemy)
{
	enemy->Desactive();

	indexOfFirstCACEnemy--;

	cacEnemyPool[indexOfFirstCACEnemy] = enemy;
}

#pragma endregion

#pragma region ShooterEnemy

ShooterEnemy* PoolManager::ExtractShooterEnemy()
{
	if (indexOfFirstShooterEnemy >= currentNumShooterEnemy) AddShooterEnemyInPool();

	ShooterEnemy* pEnemy = shooterEnemyPool[indexOfFirstShooterEnemy];

	shooterEnemyPool[indexOfFirstShooterEnemy] = nullptr;
	indexOfFirstShooterEnemy++;

	return pEnemy;
}

ShooterEnemy* PoolManager::GetShooterEnemy(CustomVector2f position, float health, Player* player)
{
	ShooterEnemy* pEnemy = ExtractShooterEnemy();

	pEnemy->team = Team::Enemy;
	pEnemy->position = position;
	pEnemy->health;
	// TO DO : Give player

	pEnemy->Active();

	return pEnemy;
}

void PoolManager::AddShooterEnemyInPool()
{
	currentNumShooterEnemy += 10;

	shooterEnemyPool.resize(currentNumShooterEnemy, nullptr);

	for (int i = indexOfFirstShooterEnemy; i < currentNumShooterEnemy; i++)
	{
		shooterEnemyPool[i] = new ShooterEnemy();
	}
}

void PoolManager::ReturnEnemy(ShooterEnemy* enemy)
{
	enemy->Desactive();

	indexOfFirstShooterEnemy--;

	shooterEnemyPool[indexOfFirstShooterEnemy] = enemy;
}

#pragma endregion

PoolManager::~PoolManager()
{
	for (int i = 0; i < currentNumBullets; i++)
	{
		if (bulletPool[i] != nullptr)
		{
			delete bulletPool[i];
		}
	}

	for (int i = 0; i < currentNumCACEnemy; i++)
	{
		if (cacEnemyPool[i] != nullptr)
		{
			delete cacEnemyPool[i];
		}
	}

	for (int i = 0; i < currentNumShooterEnemy; i++)
	{
		if (shooterEnemyPool[i] != nullptr)
		{
			delete shooterEnemyPool[i];
		}
	}
}