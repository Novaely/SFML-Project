#pragma once
#include "CustomVector2f.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

enum class CharaType { None, Player, CACEnemy, ShooterEnemy, Bullet, Lighting };
enum class ColorType { None = 0, Red = 1, Blue = 2, Green = 3 };
enum class Team { None, Player, Enemy };
int RandomInt(int min, int max);
float RandomFloat(float min, float max);


namespace Math
{
	const float PI = 3.14159265358979323846f;

	float Clamp(float value, float min, float max);

	CustomVector2f Polar2Cart(float angle, float radius);
	float ToRad(float angle);
	float ToDegree(float angle);

	float DistancePointToSegment(CustomVector2f point, CustomVector2f segPointA, CustomVector2f segPointB);

	CustomVector2f RotatePoint(CustomVector2f point, CustomVector2f origin, float angle);
} 