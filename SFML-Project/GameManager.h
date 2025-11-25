#pragma once
#include "Manager.h"
#include "Player.h"

class GameManager :
    public Manager
{
    // Constructors
    GameManager();


    int _score;
    int _multiplicateur;
	float _timerBonusScore;
    float _timerBonusScoreCheck;

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

