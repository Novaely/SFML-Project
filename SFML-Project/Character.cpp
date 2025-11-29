#include "Character.h"

Character::Character() : Movable() {}

void Character::Update(float deltaTime)
{
	Movable::Update(deltaTime);

	Rotate(deltaTime);

	if (chronoShootAgain <= timerShootAgain) {
		chronoShootAgain += deltaTime;
	}
    else
    {
        _canShoot = true;
    }
}

void Character::Move(float deltaTime)
{
    /*if (inputDirection.x == 0)
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
    }*/

    if (inputDirection == CustomVector2f::zero)
    {
        speed -= stopFriction * deltaTime;
    }
    else
    {
        if (inputDirection.Dot(moveDirection) >= 0)
        {
            speed += acceleration * deltaTime;
            moveDirection = moveDirection + (inputDirection - moveDirection) * directionChangeSpeed * deltaTime;
        }
        else
        {
            //speed -= turnBackFriction * deltaTime;
            moveDirection = moveDirection + (inputDirection - moveDirection) * turnBackDirectionChangeSpeed * deltaTime;
        }
        
        if (moveDirection.DistanceTo(inputDirection) <= diretionChangeTreshold)
        {
            moveDirection = inputDirection;
        }
    }

    Movable::Move(deltaTime);

   //std::cout << "MoveDir: X:" << moveDirection.x << " Y: " << moveDirection.y << " Speed: " << speed.x << std::endl;
}

void Character::Rotate(float deltaTime)
{
    if (rotationDirection != 0) {
        rotation += rotationDirection * rotationSpeed * deltaTime;
    }
    rotation = fmodf(rotation, 360);
}

bool Character::CanShoot() const
{
    return _canShoot;
}

CustomVector2f Character::GetLookDirection()
{
    float angle = Math::ToRad(rotation);

    return Math::Polar2Cart(angle, 1);
}