#include "Movable.h"

Movable::Movable() : GameObject() {}

void Movable::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    Move(deltaTime);
}

void Movable::Move(float deltaTime)
{
    speed = Math::Clamp(speed, 0, maxInputSpeed);
    position += moveDirection * speed * deltaTime;
}

