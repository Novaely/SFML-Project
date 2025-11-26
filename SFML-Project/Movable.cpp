#include "Movable.h"

Movable::Movable() : GameObject() {}

void Movable::Update(float deltaTime, sf::RenderWindow& window)
{
    GameObject::Update(deltaTime, window);

    Move(deltaTime);
    Rotate(deltaTime);
}

void Movable::Move(float deltaTime)
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

    speed.x = Math::Clamp(speed.x, 0, maxInputSpeed);
    speed.y = Math::Clamp(speed.y, 0, maxInputSpeed);
    position += moveDirection * speed * deltaTime;
}

void Movable::Rotate(float deltaTime)
{
    if (rotationDirection != 0) {
        rotation += rotationDirection * rotationSpeed * deltaTime;
    }
    rotation = fmodf(rotation, 360);
}
