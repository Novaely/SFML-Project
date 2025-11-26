#pragma once
#include "Enemy.h"

class CACEnemy :
    public Enemy
{
    public:
        CACEnemy();
        float detectionRadius = 0.0f;
        float attackRadius = 0.0f;
        float timeBetweenAttacks = 1.0f;
        float attackTimer = 0.0f;
        float damage = 0.0f;
        void Active() override;
        void Desactive() override;
        void Update(float deltaTime, sf::RenderWindow& window) override;
    protected:
        void ChasePlayer(float deltaTime);
		void AttackPlayer();


};

