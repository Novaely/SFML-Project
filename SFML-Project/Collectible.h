#pragma once
#include "GameObject.h"

class Collectible : public GameObject
{
	public :
		//Constructor
		Collectible();

		//Functions
		std::function<void(GameObject*)> pCollected;
		void OnCollisionEnter(GameObject* other) override;
};

