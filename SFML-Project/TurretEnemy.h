#pragma once
#include "ShooterEnemy.h"
class TurretEnemy : public ShooterEnemy
{
	public:
		TurretEnemy();

		std::function<void(TurretEnemy&)> OnShoot;

	protected:
		void TryShoot() override;
};