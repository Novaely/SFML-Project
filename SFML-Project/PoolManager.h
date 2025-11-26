#pragma once

#include "Manager.h"
#include "Bullet.h"

class PoolManager : public Manager
{
	public:
		PoolManager();
		Bullet& GetBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage);

		void ReturnBullet(Bullet& bullet);

	private:
		int startNumBullets = 100;

		int indexOfFirstBullet;
		int currentNumBullets;
		std::vector<Bullet*> bulletPool;

		Bullet* ExtractBullet();
		void AddBulletInPool();
};