#pragma once
#include "Enemy.h"
#include <functional>

class ShooterEnemy :
    public Enemy
{
    public:
        ShooterEnemy();
        float attackRadius = 0.0f;

        std::function<void(ShooterEnemy&)> OnShoot;

        void Update(float deltaTime) override;

    protected:
        virtual void TryShoot();
};

