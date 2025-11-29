#include "Movable.h"

Movable::Movable() : GameObject() {}

void Movable::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    Move(deltaTime);
}

void Movable::Move(float deltaTime)
{
    /*float vecSpeed = speed.GetMagnitude();
    vecSpeed = Math::Clamp(vecSpeed, 0, maxInputSpeed);

    position += moveDirection * vecSpeed * deltaTime;

    CustomVector2f test = moveDirection * speed;
    float length = test.GetMagnitude();

    std::cout << "Velocity X: " << test.x << " Velocity Y: " << test.y << " Velocity Length : " << length << std::endl;
    std::cout << "Speed: " << vecSpeed << std::endl;*/

    //speed.x = Math::Clamp(speed.x, 0, maxInputSpeed);
    //speed.y = Math::Clamp(speed.y, 0, maxInputSpeed);

    speed = Math::Clamp(speed, 0, maxInputSpeed);
    position += moveDirection * speed * deltaTime;

    //CustomVector2f test = moveDirection * speed;
    //float length = test.GetMagnitude();

    //std::cout << "Velocity X: " << test.x << " Velocity Y: " << test.y << " Velocity Length : " << length << std::endl;
    //std::cout << "Speed X: " << speed.x << " Speed Y: " << speed.y << std::endl;
}

