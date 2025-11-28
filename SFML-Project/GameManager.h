#pragma once

#include "Manager.h"
#include <list>
#include "PoolManager.h"

class GameManager : public Manager
{
public :
    // Constructors
    GameManager();
    ~GameManager();

    //Singleton
    static GameManager* GetInstance();


    int score;
    int multiplicateur;
	float timerBonusScore;
    float timerBonusScoreCheck;
    float timerSpawnEnemies;
    float chronoSpawnEnemies;
    bool wantSpawnEnemy;

    Player* player = nullptr;
    PoolManager* poolManager = nullptr;
	std::list<CACEnemy*> cacEnemy;
	std::list<ShooterEnemy*> shooterEnemy;
	std::list<Bullet*> bullets;
    std::list<Collectible*> collectibles;

    void Update(float deltaTime, CustomVector2f windowSize);
    void Draw(sf::RenderWindow& window);

    void PlayerShoot();
    //fonction creation
    void CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType);
    void CreateCollectible(); //not implement
    void CreateCacEnemy(CustomVector2f position, float health);
    void CreateShooterEnemy(CustomVector2f position, float health);
    //fonction destruction
    void UpdateDestroyItem();
    void DestroyBullet(GameObject* bullet);



private: 
    /// <summary>
    /// score *2 sur x temps
    /// regen vie
    /// power up direction de tir 
    /// </summary>

    void BonusScore(float timer, int multiplicateur);

	void BonusVie(float vieRegen);

    void BonusTir();

    void UpdateAll(float deltaTime);

    //Singleton
    static GameManager* _instance;

    std::list<CACEnemy*> cacEnemyToDestroy;
    std::list<ShooterEnemy*> shooterEnemyToDestroy;
    std::list<Bullet*> bulletsToDestroy;
    std::list<Collectible*> collectiblesToDestroy;
};

