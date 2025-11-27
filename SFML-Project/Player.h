#pragma once
#include "Character.h"


class GameManager;

class Player :
    public Character
{
private:
    int _levelShooter = 1;

public:
    //constructer
    Player();

    GameManager* gameManager = nullptr;
    int GetlevelShooter() const;
    void SetlevelShooter(int val);
    __declspec(property(get = GetlevelShooter, put = SetlevelShooter)) int LevelShooter;

    void SwitchColor();
    void Shoot();
    void OnCollisionEnter(GameObject* other) override;
};

