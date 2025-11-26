#include "Movable.h"

Movable::Movable() : GameObject() {}

void Movable::Update(float deltaTime, sf::RenderWindow& window)
{
    GameObject::Update(deltaTime, window);

    Move(deltaTime);
}

void Movable::Move(float deltaTime)
{
    if (inputDirection.x == 0 && inputDirection.y && 0)
    {
        speed -= stopFriction * deltaTime;
    }
    else
    {
        float dotCalc = inputDirection.Dot(moveDirection);

        if (dotCalc >= 0)
        {
            speed += acceleration * deltaTime;
            moveDirection = inputDirection;
        }
        else
        {
            speed -= turnBackFriction * deltaTime;
            if (speed <= 0)
            {
                moveDirection = inputDirection;
                speed = 0;
            }
        }
    }

    speed = Math::Clamp(speed, 0, maxInputSpeed);
    position += moveDirection * speed * deltaTime;
}