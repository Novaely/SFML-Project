#include "PoolManager.h"

PoolManager::PoolManager()
	: bulletPool(startNumBullets, nullptr)
{
	for (int i = 0; i < startNumBullets; i++)
	{
		bulletPool[i] = new Bullet;
	}

	currentNumBullets = startNumBullets;
	indexOfFirstBullet = 0;
}

Bullet* PoolManager::ExtractBullet()
{
	if (indexOfFirstBullet >= currentNumBullets) AddBulletInPool();

	Bullet* pBullet = bulletPool[indexOfFirstBullet];

	bulletPool[indexOfFirstBullet] = nullptr;
	indexOfFirstBullet++;

	return pBullet;
}

Bullet& PoolManager::GetBullet()
{
	Bullet* pBullet = ExtractBullet();

	return *pBullet;
}

Bullet& PoolManager::GetBullet(Team team)
{
	Bullet* pBullet = ExtractBullet();

	//Team

	return *pBullet;
}

Bullet& PoolManager::GetBullet(Team team, float speed, float damages)
{
	Bullet* pBullet = ExtractBullet();

	// Team
	pBullet->speed = speed;
	pBullet->damage = damages;

	return *pBullet;
}

void PoolManager::AddBulletInPool()
{
	currentNumBullets++;
	
	bulletPool.resize(currentNumBullets, nullptr);
	bulletPool[currentNumBullets - 1] = new Bullet();

	indexOfFirstBullet = currentNumBullets - 2;
}

void PoolManager::ReturnBullet(Bullet& bullet)
{
	bullet.Desactive();

	indexOfFirstBullet--;

	bulletPool[indexOfFirstBullet] = &bullet;
}