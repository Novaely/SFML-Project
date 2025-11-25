#pragma once
#include "CustomVector2f.h"
#include <SFML/Graphics.hpp>

enum class ColorType { None, Rouge, Bleu, Vert };
enum class Team {None, Player, Enemy };

namespace Math
{
	float Clamp(float value, float min, float max);
}

