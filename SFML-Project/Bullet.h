#pragma once
#include "Movable.h"

class Bullet :
    public Movable
{

    public:
        // Constructor 
        Bullet();

        void Active() override;
		void Desactive() override;
};

