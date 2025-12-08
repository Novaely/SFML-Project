#pragma once
#include "Movable.h"

class Character : public Movable
{
public:
	Character();
	float health = 0;
	float speedBullet = 0;
	float timerShootAgain = 0;
	float chronoShootAgain = 0;

	float acceleration = 0;
	float stopFriction = 0;
	//float turnBackFriction = 0;

	float diretionChangeTreshold = 0.05f;
	float directionChangeSpeed = 5;
	float turnBackDirectionChangeSpeed = 2.5f;

	float rotationSpeed = 0;
	float rotationDirection = 0;

	CustomVector2f bulletSpawnPos = CustomVector2f::zero;

	bool CanShoot() const;
	void Update(float deltaTime) override;
	void Move(float deltaTime) override;
	void Rotate(float deltaTime);

	CustomVector2f GetLookDirection();

protected:
	bool _canShoot = true;
	virtual void Damage(float dmg);
};