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

    Player* player = nullptr;

    std::list<GameObject*> gameObjects;

    PoolManager* poolManager = nullptr;

    void Update(float deltaTime, CustomVector2f windowSize);
    void Draw(sf::RenderWindow& window) override;
    void UpdateDestroyItem();

    void PlayerShoot();
    //fonction creation
    void CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType);
    LightningNode* CreateLightning(Team team, CustomVector2f position, CustomVector2f direction, float damage);
    void CreateCollectible(CustomVector2f position); //not implemented
    void CreateCacEnemy(CustomVector2f position, float health, ColorType color);
    void CreateShooterEnemy(CustomVector2f position, float health, ColorType color);
    void CreateTurretEnemy(CustomVector2f position, float health, ColorType color);
    void SpawnEnemy(CustomVector2f windowSize);

    void DestroyCacEnemy(GameObject* item);
    void DestroyShooterEnemy(GameObject* item);
    void DestroyTurretEnemy(GameObject* item);

    //fonction get
    int GetPlayerHealth() const;
    float GetTime();
    int GetMultiplicateur() const;

private: 

    float _time = 0;
    int _scoreUpdate;
    int _multiplicateur;
    float _timerBonusScore;
    float _timerBonusScoreCheck;
    float _timerSpawnEnemies;
    float _chronoSpawnEnemies;
    bool _wantSpawnEnemy;

    int _idGameObjectCreateListener = -1;

    /// <summary>
    /// score *2 sur x temps
    /// regen vie
    /// power up direction de tir 
    /// </summary>

    void UpdateAll(float deltaTime);

    //foncion bonus
    void BonusScore(float timer, int multiplicateur);
	void BonusVie(float vieRegen);
    void BonusTir();

    //fonction shoot
    void OnEnemyShoot(ShooterEnemy& enemy);
    void OnTurretEnemyShoot(TurretEnemy& enemy);

    //Singleton
    static GameManager* _instance;

    void NewGameObjectCreated(GameObject* go);
};

