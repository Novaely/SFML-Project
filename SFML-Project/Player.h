#pragma once
#include "Character.h"

class Player : public Character
{
private:
    int _levelShooter = 1;
protected:
    void Damage(float dmg) override;

public:
    //constructer
    Player();

    int GetlevelShooter() const;
    void SetlevelShooter(int val);
    __declspec(property(get = GetlevelShooter, put = SetlevelShooter)) int LevelShooter;

    void SwitchColor();
    void Shoot();
    void OnCollisionEnter(GameObject* other) override;



};

