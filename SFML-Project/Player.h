#pragma once
#include "Character.h"

class Player :
    public Character
{
    private : 
        int _levelShooter = 1;
        
    public:
        Player();

        int GetlevelShooter();
        void SetlevelShooter(int val);
        __declspec(property(get = GetlevelShooter, put = SetlevelShooter)) int LevelShooter;

        void SwitchColor();
};

