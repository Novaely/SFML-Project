#pragma once
#include "GameObject.h"

class Collectible : public GameObject
{
	public :
		Collectible();

		std::function<void(GameObject*)> pCollected;
		void OnCollisionEnter(GameObject* other) override;

	private :
		float _lifeTime;
		float _chrono = 0;
};

