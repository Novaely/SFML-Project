#pragma once
#include "CustomVector2f.h"

enum class ColorType { None = 0, Rouge = 1, Bleu = 2, Vert = 3};

namespace Math
{
	float Clamp(float value, float min, float max);
}

