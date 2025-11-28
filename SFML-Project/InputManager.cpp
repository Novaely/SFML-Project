#include "InputManager.h"
#include <iostream>
#include "Utils.h"

InputManager::InputManager()
{
    gameManager = GameManager::GetInstance();
}

void InputManager::OneClickInputPressed(sf::Event event, Player& player)
{
    if (event.key.code == sf::Keyboard::LShift) {
        if (!LShiftPressed) {
            LShiftPressed = true;
            player.SwitchColor();
        }
        
    }
}

void InputManager::OneClickInputUnpressed(sf::Event event)
{
    if (event.key.code == sf::Keyboard::LShift) {
        LShiftPressed = false;
    }
}



void InputManager::ContinuInputCheck(sf::Event event, Player & player) {
    bool keyUp = (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    bool keyDown = (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    bool keyLeft = (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    bool keyRight = (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
    CustomVector2f inputDirection = { (float)keyRight - (float)keyLeft, (float)keyDown - (float)keyUp };
    player.inputDirection = inputDirection.GetNormalised();

    bool keyRotLeft = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool keyRotRight = sf::Keyboard::isKeyPressed(sf::Keyboard::E);
    player.rotationDirection = (float)keyRotRight - (float)keyRotLeft;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        gameManager->PlayerShoot();
    }
}