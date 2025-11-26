#pragma once
#include "Manager.h"
#include "Player.h"
#include "CACEnemy.h"
#include "ShooterEnemy.h"
#include "Bullet.h"
#include <list>

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

    Player player;
	std::list<CACEnemy*> cacEnemy;
	std::list<ShooterEnemy*> shooterEnemy;
	std::list<Bullet*> bullets;

private: 
    /// <summary>
    /// score *2 sur x temps
    /// regen vie
    /// power up direction de tir 
    /// </summary>

    void Update(float deltaTime);

    void BonusScore(float timer, int multiplicateur);

	void BonusVie(Player& player, float vieRegen);

    void BonusTir(Player& player);


};

