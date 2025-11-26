#pragma once
#include "CustomVector2f.h"
#include <SFML/Graphics.hpp>

enum class ColorType { None = 0, Rouge = 1, Bleu = 2, Vert = 3 };
enum class Team { None, Player, Enemy };

namespace Math
{
	const float PI = 3.14159265358979323846f;

	float Clamp(float value, float min, float max);

	CustomVector2f Polar2Cart(float angle, float radius);
	float ToRad(float angle);
	float ToDegree(float angle);
}