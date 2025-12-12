#pragma once
#include "Enemy.h"
#include <functional>

class ShooterEnemy : public Enemy
{
    public:
        // Constructor 
        ShooterEnemy();
        // Variables
        float attackRadius = 0.0f;

		// Functions
        std::function<void(ShooterEnemy&)> OnShoot;
        void Update(float deltaTime) override;

    protected:
        //Functions
        virtual void TryShoot();
};

