#pragma once
#include "ShooterEnemy.h"
#include "LightningNode.h"

class TurretEnemy : public ShooterEnemy
{
	public:
		LightningNode* lastLightningShooted = nullptr;

		TurretEnemy();

		std::function<void(TurretEnemy&)> OnShoot;

	protected:
		void TryShoot() override;
		void Damage(float dmg) override;
};