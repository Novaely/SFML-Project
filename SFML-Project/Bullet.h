#pragma once
#include "Movable.h"

class Bullet :
    public Movable
{

    // Constructor 
    Bullet();



    public:
        float damage;

        void Active();
		void Desactive();
};

