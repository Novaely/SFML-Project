#pragma once

#include "Manager.h"

class PoolManager : public Manager
{
	public:
		PoolManager();
		~PoolManager();

		Bullet* GetBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType);
		CACEnemy* GetCACEnemy(CustomVector2f position, float health, Player* player);
		ShooterEnemy* GetShooterEnemy(CustomVector2f position, float health, Player* player);
		TurretEnemy* GetTurretEnemy(CustomVector2f position, float health, Player* player);

		void ReturnBullet(Bullet* bullet);
		void ReturnEnemy(CACEnemy* enemy);
		void ReturnEnemy(ShooterEnemy* enemy);
		void ReturnEnemy(TurretEnemy* enemy);

	private:
		// Bullets
		int startNumBullets = 100;

		int indexOfFirstBullet = 0;
		int currentNumBullets;
		std::vector<Bullet*> bulletPool;

		Bullet* ExtractBullet();
		void AddBulletInPool();

		// CACEnemy
		int startNumCACEnemy = 50;

		int indexOfFirstCACEnemy = 0;
		int currentNumCACEnemy;
		std::vector<CACEnemy*> cacEnemyPool;

		CACEnemy* ExtractCACEnemy();
		void AddCACEnemyInPool();

		// ShooterEnemy
		int startNumShooterEnemy = 20;

		int indexOfFirstShooterEnemy = 0;
		int currentNumShooterEnemy;
		std::vector<ShooterEnemy*> shooterEnemyPool;
		
		ShooterEnemy* ExtractShooterEnemy();
		void AddShooterEnemyInPool();

		// TurretEnemy
		int startNumTurretEnemy = 10;

		int indexOfFirstTurretEnemy = 0;
		int currentNumTurretEnemy;
		std::vector<TurretEnemy*> turretEnemyPool;

		TurretEnemy* ExtractTurretEnemy();
		void AddTurretEnemyInPool();
};