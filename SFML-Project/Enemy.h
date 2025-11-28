#pragma once
#include "Character.h"

class Enemy :
    public Character
{
    public:
        // Constructor 
        Enemy();

        CustomVector2f* targetPos = nullptr;

        void Active() override;
        void Desactive() override;

        void OnCollisionEnter(GameObject* other) override;

     
};

