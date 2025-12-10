#pragma once
#include "Character.h"
#include "LightningNode.h"

class Player : public Character
{
private:
    int _levelShooter = 1;
    int _levelShooterMax = 3;
    bool _isInvicible = false;
    float _invicibleTime = 2.0f;
	float _timeSinceInvincible = 0.0f;
	float _timeSinceColorChange = 0.0f;
protected:
    void Damage(float dmg) override;

public:
    //constructer
    Player();


	void Update(float deltaTime) override;

    int GetlevelShooter() const;
    void SetlevelShooter(int val);
    __declspec(property(get = GetlevelShooter, put = SetlevelShooter)) int LevelShooter;

    void SwitchColor();
    void Shoot();
    void OnCollisionEnter(GameObject* other) override;
    float GetMaxHealth() const;
};