#pragma once
#include "Movable.h"

class Character : public Movable
{
public:
	// Constructor
	Character();

	// Variables
	float health = 0;
	float maxHealth = 0;
	float speedBullet = 0;
	float timerShootAgain = 0;
	float chronoShootAgain = 0;
	float acceleration = 0;
	float stopFriction = 0;
	float turnBackFriction = 0;
	float rotationSpeed = 0;
	float rotationDirection = 0;

	CustomVector2f bulletSpawnPos = CustomVector2f::zero;

	// Functions
	void Update(float deltaTime) override;
	void Move(float deltaTime) override;
	bool CanShoot() const;
	void Rotate(float deltaTime);

	CustomVector2f GetLookDirection();

protected:
	// Variables
	Vec2f velocity = Vec2f::zero;
	bool _canShoot = true;

	// Functions
	virtual void Damage(float dmg);
};