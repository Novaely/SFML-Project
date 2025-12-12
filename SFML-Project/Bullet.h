#pragma once
#include "Movable.h"

class Bullet : public Movable
{
    public:
        // Constructor 
        Bullet();

        // Functions
        void Active() override;
		void Desactive() override;
        void OnCollisionEnter(GameObject* other) override;
};

