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

    int score = 0;
    int fps = 0;
    bool pause = false;

    Player* player = nullptr;

    std::list<GameObject*> gameObjects;

    PoolManager* poolManager = nullptr;

    void Update(float deltaTime, CustomVector2f& windowSize);
    void Draw(sf::RenderWindow& window, const Vec2f& _scaleRaio);
    void UpdateDestroyItem();

    void RestartGame();

    void PlayerShoot();
    //fonction creation
    void CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType);
    LightningNode* CreateLightning(Team team, CustomVector2f position, CustomVector2f direction, float damage);

    void DestroyCacEnemy(GameObject* item);
    void DestroyShooterEnemy(GameObject* item);
    void DestroyTurretEnemy(GameObject* item);

    //fonction get
    int GetPlayerHealth() const;
    float GetTime();
    int GetMultiplicateur() const;
    int GetLevel() const;
    int GetFPS() const;

private: 
    //variable
    float _time = 0;
    int _idGameObjectCreateListener = -1;

    //variable bonus
    int _scoreUpdate;
    int _multiplicateur;
    float _timerBonusScore;
    float _timerBonusScoreCheck;

    //variable enemy
    int _numberOfEnemyForWave;
    int _numberOfEnemyUp;
    int _numberOfWaveBeforeUpNumberOfEnemy;
    float _timerSpawnEnemies;
    float _chronoSpawnEnemies;
    int _wave;
    float _timeBeforefirstEnemy = 2.0f;
    float _radiusSpawnEnemy = 250;
    float _screenPading = 10;

    void UpdateAll(float deltaTime, CustomVector2f& windowSize);

    bool IsPosOutOfBounds(Vec2f& pos, Vec2f& bounds);
    void StickGameObjectInBounds(GameObject& go, Vec2f& bounds);

    Vec2f GetRandomPosForEnemy();

    //foncion bonus
    void BonusScore(float timer, int multiplicateur);
	void BonusVie(float vieRegen);
    void BonusTir();

    //fonction shoot
    void OnEnemyShoot(ShooterEnemy& enemy);
    void OnTurretEnemyShoot(TurretEnemy& enemy);

    //Singleton
    static GameManager* _instance;

    std::list<Enemy*> _enemies;

    void NewGameObjectCreated(GameObject* go);

    //spawn
    void SpawnWaveEnemy(CustomVector2f windowSize);
    void SpawnEnemy(CustomVector2f windowSize);
    void CreateCacEnemy(CustomVector2f position, float health, ColorType color);
    void CreateShooterEnemy(CustomVector2f position, float health, ColorType color);
    void CreateTurretEnemy(CustomVector2f position, float health, ColorType color);
    void CreateCollectible(CustomVector2f position);
};

