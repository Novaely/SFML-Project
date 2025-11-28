#pragma once
#include "Enemy.h"

class CACEnemy :
    public Enemy
{
    public:
        CACEnemy();

        void Update(float deltaTime) override;
};

