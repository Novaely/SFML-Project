#include "Movable.h"

Movable::Movable() : GameObject() {}

void Movable::Update(float deltaTime, sf::RenderWindow& window)
{
    GameObject::Update(deltaTime, window);

    Move(deltaTime);
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

    /*float vecSpeed = speed.GetMagnitude();
    vecSpeed = Math::Clamp(vecSpeed, 0, maxInputSpeed);

    position += moveDirection * vecSpeed * deltaTime;

    CustomVector2f test = moveDirection * speed;
    float length = test.GetMagnitude();

    std::cout << "Velocity X: " << test.x << " Velocity Y: " << test.y << " Velocity Length : " << length << std::endl;
    std::cout << "Speed: " << vecSpeed << std::endl;*/

    speed.x = Math::Clamp(speed.x, 0, maxInputSpeed);
    speed.y = Math::Clamp(speed.y, 0, maxInputSpeed);
    position += moveDirection * speed * deltaTime;

    //CustomVector2f test = moveDirection * speed;
    //float length = test.GetMagnitude();

    //std::cout << "Velocity X: " << test.x << " Velocity Y: " << test.y << " Velocity Length : " << length << std::endl;
    //std::cout << "Speed X: " << speed.x << " Speed Y: " << speed.y << std::endl;
}