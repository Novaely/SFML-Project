#pragma once
#include "Character.h"

class Enemy : public Character
{
    public:
        // Constructor 
        Enemy();

        // Variables
        CustomVector2f* targetPos = nullptr;

        //Functions
        void Active() override;
        void Desactive() override;

        void OnCollisionEnter(GameObject* other) override;

     
};

