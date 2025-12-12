#pragma once
#include "Player.h"
#include "GameManager.h"
#include <SFML/Graphics.hpp>

class InputManager :
    public Manager
{
    public :
        // Constructor
        InputManager();

        // Function
        void OneClickInputPressed(sf::Event event, Player& player);
        void OneClickInputUnpressed(sf::Event event);
        void ContinuInputCheck(sf::Event event, Player& player);

    private:
        // Variable
        GameManager* _gameManager = nullptr;
        bool _leftShiftPressed = false;
};