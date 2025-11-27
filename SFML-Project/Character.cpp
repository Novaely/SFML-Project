#include "Character.h"

Character::Character() : Movable() {


}

void Character::Update(float deltaTime, sf::RenderWindow& window) {
	Movable::Update(deltaTime, window);

	Rotate(deltaTime);

	if (chronoShootAgain <= timerShootAgain) {
		chronoShootAgain += deltaTime;
	}
}

void Character::Move(float deltaTime)
{
    if (inputDirection.x == 0)
    {
        speed.x -= stopFriction * deltaTime;
    }
    else
    {
        if (inputDirection.x * moveDirection.x >= 0)
        {
            speed.x += acceleration * deltaTime;
            moveDirection.x = inputDirection.x;
        }
        else
        {
            speed.x -= turnBackFriction * deltaTime;
            if (speed.x <= 0)
            {
                speed.x = 0;
                moveDirection.x = inputDirection.x;
            }
        }
    }

    if (inputDirection.y == 0)
    {
        speed.y -= stopFriction * deltaTime;
    }
    else
    {
        if (inputDirection.y * moveDirection.y >= 0)
        {
            speed.y += acceleration * deltaTime;
            moveDirection.y = inputDirection.y;
        }
        else
        {
            speed.y -= turnBackFriction * deltaTime;
            if (speed.y <= 0)
            {
                speed.y = 0;
                moveDirection.y = inputDirection.y;
            }
        }
    }

    Movable::Move(deltaTime);
}

void Character::Rotate(float deltaTime)
{
    if (rotationDirection != 0) {
        rotation += rotationDirection * rotationSpeed * deltaTime;
    }
    rotation = fmodf(rotation, 360);
}