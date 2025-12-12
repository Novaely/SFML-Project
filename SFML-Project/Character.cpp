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
    // If no inputs, apply stop friction
    if (inputDirection == Vec2f::zero && velocity != Vec2f::zero)
    {
        Vec2f frictionDir = -velocity.GetNormalised();
        velocity += frictionDir * stopFriction * deltaTime;

        if (velocity.Dot(velocity + frictionDir * stopFriction * deltaTime) < 0)
        {
            velocity = Vec2f::zero;
        }
    }
    else
    {
        // If Inputs direction close to mvoe direction apply acceleration
        if (inputDirection.Dot(moveDirection) >= 0)
        {
            velocity += inputDirection * acceleration * deltaTime;
        }
        // Else apply turn back friction
        else
        {
            velocity += inputDirection * turnBackFriction * deltaTime;
        }
    }

    if (velocity.GetSquaredMagnitude() > maxInputSpeed * maxInputSpeed)
    {
        velocity.SetMagnitude(maxInputSpeed);
    }

    position += velocity * deltaTime;
}

bool Character::CanShoot() const
{
    return _canShoot;
}

void Character::Rotate(float deltaTime)
{
    if (rotationDirection != 0) {
        rotation += rotationDirection * rotationSpeed * deltaTime;
    }
    rotation = fmodf(rotation, 360);
}

CustomVector2f Character::GetLookDirection()
{
    float angle = Math::ToRad(rotation);

    return Math::Polar2Cart(angle, 1);
}

void Character::Damage(float dmg)
{
    health -= dmg;
    if (health <= 0)
    {
        Destroy();
    }
}