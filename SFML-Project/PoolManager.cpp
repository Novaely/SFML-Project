#include "PoolManager.h"

PoolManager::PoolManager()
	: bulletPool(startNumBullets, new Bullet())
{
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