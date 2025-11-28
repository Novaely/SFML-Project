#pragma once
#include "Player.h"
#include "GameManager.h"
#include <SFML/Graphics.hpp>

class InputManager :
    public Manager
{
    public :
        void OneClickInputPressed(sf::Event event, Player& player);
        void OneClickInputUnpressed(sf::Event event);
        void ContinuInputCheck(sf::Event event, Player& player);
        InputManager();

    private:
        GameManager* gameManager = nullptr;
        bool LShiftPressed = false;
};