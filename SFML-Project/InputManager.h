#pragma once
#include "Manager.h"
#include "Player.h"
#include <SFML/Graphics.hpp>

class InputManager :
    public Manager
{
    public :
        void InputCheck(sf::Event event, Player& player);
        InputManager();
};

