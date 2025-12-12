#pragma once
#include "Enemy.h"

class CACEnemy : public Enemy
{
    public:
        // Constructors
        CACEnemy();

        // Functions
        void Active() override;
        void Desactive() override;
        void Update(float deltaTime) override;

    protected:
        //Functions
        void ChasePlayer(float deltaTime);
		void AttackPlayer();
};

