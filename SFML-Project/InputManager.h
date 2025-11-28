#pragma once
#include "Player.h"
#include "GameManager.h"
#include <SFML/Graphics.hpp>

class InputManager :
    public Manager
{
    public :
        void OneClickInputCheck(sf::Event event, Player& player);
        void ContinuInputCheck(sf::Event event, Player& player);
        InputManager();

    private:
        GameManager* gameManager = nullptr;
};