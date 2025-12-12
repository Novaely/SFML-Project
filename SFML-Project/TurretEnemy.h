#pragma once
#include "ShooterEnemy.h"
#include "LightningNode.h"

class TurretEnemy : public ShooterEnemy
{
	public:
		// Constructor
		TurretEnemy();

		// Variables
		LightningNode* lastLightningShooted = nullptr;

		//Functions
		std::function<void(TurretEnemy&)> OnShoot;

	protected:
		//Functions
		void TryShoot() override;
		void Damage(float dmg) override;
};