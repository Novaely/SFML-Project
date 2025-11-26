#include "PoolManager.h"

PoolManager::PoolManager() : bulletPool(startNumBullets, new Bullet()), cacEnemyPool(startNumCACEnemy, new Enemy())
{
	currentNumBullets = startNumBullets;

	currentNumCACEnemy = startNumCACEnemy;
}

#pragma region Bullets

Bullet* PoolManager::ExtractBullet()
{
	if (indexOfFirstBullet >= currentNumBullets) AddBulletInPool();

	Bullet* pBullet = bulletPool[indexOfFirstBullet];

	bulletPool[indexOfFirstBullet] = nullptr;
	indexOfFirstBullet++;

	return pBullet;
}

Bullet& PoolManager::GetBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage)
{
	Bullet* pBullet = ExtractBullet();

	pBullet->team = team;
	pBullet->position = position;
	pBullet->speed = CustomVector2f(speed);
	pBullet->inputDirection = direction;
	pBullet->damage = damage;

	pBullet->Active();

	return *pBullet;
}

void PoolManager::AddBulletInPool()
{
	currentNumBullets += 10;

	bulletPool.resize(currentNumBullets, new Bullet());
}

void PoolManager::ReturnBullet(Bullet& bullet)
{
	bullet.Desactive();

	indexOfFirstBullet--;

	bulletPool[indexOfFirstBullet] = &bullet;
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

CACEnemy& PoolManager::GetCACEnemy(CustomVector2f position, float health, Player* player)
{
	CACEnemy* pEnemy = ExtractCACEnemy();

	pEnemy->team = Team::Enemy;
	pEnemy->position = position;
	pEnemy->health;
	// TO DO : Give player

	pEnemy->Active();

	return *pEnemy;
}

void PoolManager::AddCACEnemyInPool()
{
	currentNumCACEnemy += 10;

	cacEnemyPool.resize(currentNumCACEnemy, new CACEnemy());
}

void PoolManager::ReturnEnemy(CACEnemy& enemy)
{
	enemy.Desactive();

	indexOfFirstCACEnemy--;

	cacEnemyPool[indexOfFirstCACEnemy] = &enemy;
}

#pragma endregion

