#pragma once
#include "Character.h"

class Player : public Character
{
public:
    //constructer
    Player();

    int GetlevelShooter() const;
    void SetlevelShooter(int val);
    __declspec(property(get = GetlevelShooter, put = SetlevelShooter)) int LevelShooter;

    void SwitchColor();
    void Shoot();

private:
    int _levelShooter = 1;
};