#pragma once
#include "Enemy.h"

class ShooterEnemy :
    public Enemy
{
public:
    ShooterEnemy();
    float attackRadius = 0.0f;

    void Update(float deltaTime) override;
};

