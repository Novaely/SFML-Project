#include "PoolManager.h"

PoolManager::PoolManager()
	: bulletPool(startNumBullets, nullptr), cacEnemyPool(startNumCACEnemy, nullptr),
	shooterEnemyPool(startNumShooterEnemy, nullptr), turretEnemyPool(startNumTurretEnemy, nullptr)
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

	for (int i = 0; i < startNumTurretEnemy; i++)
	{
		turretEnemyPool[i] = new TurretEnemy();
	}
	currentNumTurretEnemy = startNumTurretEnemy;
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

Bullet* PoolManager::GetBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType)
{
	Bullet* pBullet = ExtractBullet();

	pBullet->team = team;
	pBullet->position = position;
	pBullet->shape->setPosition(position.x, position.y);
	pBullet->speed = speed;
	pBullet->maxInputSpeed = speed;
	pBullet->moveDirection = direction;
	pBullet->damage = damage;
	pBullet->SetColor(colorType);

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

	if (indexOfFirstBullet < 0)
	{
		std::cout << "Returned a bullet but pool is full" << std::endl;
		indexOfFirstBullet = 0;
	}

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
	pEnemy->shape->setPosition(position.x, position.y);
	pEnemy->health;
	
	pEnemy->targetPos = &(player->position);

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

	if (indexOfFirstCACEnemy < 0)
	{
		std::cout << "Returned a cac enemy but pool is full" << std::endl;
		indexOfFirstCACEnemy = 0;
	}

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
	pEnemy->shape->setPosition(position.x, position.y);

	pEnemy->health;

	pEnemy->targetPos = &(player->position);

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

	if (indexOfFirstShooterEnemy < 0)
	{
		std::cout << "Returned a shooter enemy but pool is full" << std::endl;
		indexOfFirstShooterEnemy = 0;
	}

	shooterEnemyPool[indexOfFirstShooterEnemy] = enemy;
}

#pragma endregion

#pragma region TurretEnemy

TurretEnemy* PoolManager::ExtractTurretEnemy()
{
	if (indexOfFirstTurretEnemy >= currentNumTurretEnemy) AddTurretEnemyInPool();

	TurretEnemy* pEnemy = turretEnemyPool[indexOfFirstTurretEnemy];

	turretEnemyPool[indexOfFirstTurretEnemy] = nullptr;
	indexOfFirstTurretEnemy++;

	return pEnemy;
}

TurretEnemy* PoolManager::GetTurretEnemy(CustomVector2f position, float health, Player* player)
{
	TurretEnemy* pEnemy = ExtractTurretEnemy();

	pEnemy->team = Team::Enemy;
	pEnemy->position = position;
	pEnemy->shape->setPosition(position.x, position.y);

	pEnemy->health;

	pEnemy->targetPos = &(player->position);

	pEnemy->Active();

	return pEnemy;
}

void PoolManager::AddTurretEnemyInPool()
{
	currentNumTurretEnemy += 10;

	turretEnemyPool.resize(currentNumTurretEnemy, nullptr);

	for (int i = indexOfFirstTurretEnemy; i < currentNumTurretEnemy; i++)
	{
		turretEnemyPool[i] = new TurretEnemy();
	}
}

void PoolManager::ReturnEnemy(TurretEnemy* enemy)
{
	enemy->Desactive();

	indexOfFirstTurretEnemy--;

	if (indexOfFirstTurretEnemy < 0)
	{
		std::cout << "Returned a turret enemy but pool is full" << std::endl;
		indexOfFirstTurretEnemy = 0;
	}

	turretEnemyPool[indexOfFirstTurretEnemy] = enemy;
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