#pragma once
#include "GameObject.h"

class Collectible : public GameObject
{
	public :
		Collectible();

		std::function<void(GameObject*)> pCollected;

	private :
		float _lifeTime;
		float _chrono = 0;
};

