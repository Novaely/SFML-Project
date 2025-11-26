#pragma once
#include "Manager.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class InputManager :
    public Manager
{
    public :
        void OneClickInputCheck(sf::Event event, Player& player);
        void ContinuInputCheck(sf::Event event, Player& player);
        InputManager();
};

