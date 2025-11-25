#pragma once

#include "Manager.h"
#include "Bullet.h"

class PoolManager : public Manager
{
	public:
		PoolManager();
		Bullet& GetBullet();
		Bullet& GetBullet(Team team);
		Bullet& GetBullet(Team team, float speed, float damages);

		void ReturnBullet(Bullet& bullet);

	private:
		int startNumBullets = 100;

		int indexOfFirstBullet;
		int currentNumBullets;
		std::vector<Bullet*> bulletPool;

		Bullet* ExtractBullet();
		void AddBulletInPool();
};