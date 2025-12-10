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
    int fps;

    Player* player = nullptr;
    PoolManager* poolManager = nullptr;
	std::list<CACEnemy*> cacEnemy;
	std::list<ShooterEnemy*> shooterEnemy;
    std::list<TurretEnemy*> turretEnemy;
	std::list<Bullet*> bullets;
    std::list<Collectible*> collectibles;
    std::list<LightningNode*> lightnings;

    void Update(float deltaTime, CustomVector2f windowSize);
    void Draw(sf::RenderWindow& window) override;
    void UpdateDestroyItem();

    void PlayerShoot();
    //fonction creation
    void CreateBullet(Team team, CustomVector2f position, float speed, CustomVector2f direction, float damage, ColorType colorType);
    void CreateLightning(Team team, CustomVector2f position, CustomVector2f direction, float damage);
    void CreateCollectible(CustomVector2f position); //not implemented
    void CreateCacEnemy(CustomVector2f position, float health, ColorType color);
    void CreateShooterEnemy(CustomVector2f position, float health, ColorType color);
    void CreateTurretEnemy(CustomVector2f position, float health, ColorType color);
    void SpawnWaveEnemy(CustomVector2f windowSize);
    void SpawnEnemy(CustomVector2f windowSize);

    //fonction get
    int GetPlayerHealth() const;
    float GetTime();
    int GetMultiplicateur() const;
    int GetLevel() const;
    int GetFPS() const;

private: 

    float _time = 0;
    int _scoreUpdate;
    int _multiplicateur;
    float _timerBonusScore;
    float _timerBonusScoreCheck;
    int _numberOfEnemyForWave;
    int _numberOfEnemyUp;
    int _numberOfWaveBeforeUpNumberOfEnemy;
    float _timerSpawnEnemies;
    float _chronoSpawnEnemies;
    bool _wantSpawnEnemy;
    int _wave;
    CustomVector2f _radiusSpawnEnemy;

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

    //fonction destroy
    void DestroyBullet(GameObject* item);
    void DestroyLightning(GameObject* item);
    void DestroyCollectible(GameObject* item);
    void DestroyCacEnemy(GameObject* item);
    void DestroyShooterEnemy(GameObject* item);
    void DestroyTurretEnemy(GameObject* item);

    //Singleton
    static GameManager* _instance;

    std::list<CACEnemy*> _cacEnemyToDestroy;
    std::list<ShooterEnemy*> _shooterEnemyToDestroy;
    std::list<TurretEnemy*> _turretEnemyToDestroy;
    std::list<LightningNode*> _lightningToDestroy;
    std::list<Bullet*> _bulletsToDestroy;
    std::list<Collectible*> _collectiblesToDestroy;

    std::list<Enemy*> _enemies;
};

