#pragma once
#include "Character.h"

class Enemy :
    public Character
{
    public:
        // Constructor 
        Enemy();

        void Active() override;
        void Desactive() override;
        
};

