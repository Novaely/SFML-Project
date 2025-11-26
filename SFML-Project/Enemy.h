#pragma once
#include "Character.h"

class GameManager;
class Player;
class Enemy :
    public Character
{
    public:
        // Constructor 
        Enemy();


        Player* player = nullptr;
        GameManager* gameManager;


        void Active() override;
        void Desactive() override;

        void OnCollisionEnter(GameObject* other) override;

     
};

