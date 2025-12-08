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
    void Draw(sf::RenderWindow& window) override;

    void PlayerShoot();
    //fonction creation
    void CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType);
    void CreateCollectible(); //not implement
    void CreateCacEnemy(CustomVector2f position, float health, ColorType color);
    void CreateShooterEnemy(CustomVector2f position, float health, ColorType color);
    void SpawnEnemy(CustomVector2f windowSize);
    //fonction destruction
    void UpdateDestroyItem();
    void DestroyBullet(GameObject* item);
    void DestroyCacEnemy(GameObject* item);
    void DestroyShooterEnemy(GameObject* item);

    int GetPlayerHealth() const; 

    float GetTime();

private: 

    float _time = 0;

    /// <summary>
    /// score *2 sur x temps
    /// regen vie
    /// power up direction de tir 
    /// </summary>

    void BonusScore(float timer, int multiplicateur);

	void BonusVie(float vieRegen);

    void BonusTir();

    void UpdateAll(float deltaTime);

    void OnEnemyShoot(ShooterEnemy& enemy);

    //Singleton
    static GameManager* _instance;

    std::list<CACEnemy*> _cacEnemyToDestroy;
    std::list<ShooterEnemy*> _shooterEnemyToDestroy;
    std::list<Bullet*> _bulletsToDestroy;
    std::list<Collectible*> _collectiblesToDestroy;
};

