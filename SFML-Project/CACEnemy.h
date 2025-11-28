#pragma once
#include "Enemy.h"

class CACEnemy :
    public Enemy
{
    public:
        CACEnemy();
        float damage = 0.0f;

        void Active() override;
        void Desactive() override;
        void Update(float deltaTime) override;

    protected:
        void ChasePlayer(float deltaTime);
		void AttackPlayer();
};

