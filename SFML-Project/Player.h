#pragma once
#include "Character.h"
class Player :
    public Character
{
    private : 
        int _levelShoter = 1;
    public : 
        int GetlevelShoter();

        int SetlevelShoter(int va);
};

