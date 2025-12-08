#pragma once
#include "Enemy.h"

class CACEnemy :
    public Enemy
{
    public:
        CACEnemy();

        void Active() override;
        void Desactive() override;
        void Update(float deltaTime) override;

    protected:
        void ChasePlayer(float deltaTime);
		void AttackPlayer();
};

