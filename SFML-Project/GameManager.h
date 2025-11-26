#pragma once

#include "Manager.h"
#include <list>
#include "PoolManager.h"

class GameManager :
    public Manager
{
public :
    // Constructors
    GameManager();

    int score;
    int multiplicateur;
	float timerBonusScore;
    float timerBonusScoreCheck;


    Player* player = nullptr;
    PoolManager* poolManager = nullptr;
	std::list<CACEnemy*> cacEnemy;
	std::list<ShooterEnemy*> shooterEnemy;
	std::list<Bullet*> bullets;

    void Update(float deltaTime, sf::RenderWindow& window);

    void CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage);

private: 
    /// <summary>
    /// score *2 sur x temps
    /// regen vie
    /// power up direction de tir 
    /// </summary>

    void BonusScore(float timer, int multiplicateur);

	void BonusVie(float vieRegen);

    void BonusTir();

    void UpdateAll(float deltaTime, sf::RenderWindow& window);
};

