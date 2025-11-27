#include "Utils.h"

float Math::Clamp(float value, float min, float max)
{
	if (value <= min) return min;
	if (value >= max) return max;
	return value;
}

CustomVector2f Math::Polar2Cart(float angle, float radius)
{
	return CustomVector2f(cos(angle) * radius, sin(angle) * radius);
}

float Math::ToRad(float angle)
{
	return angle * PI / 180.0f;
}

float Math::ToDegree(float angle)
{
	return angle * 180.0f / PI;
}

CustomVector2f Math::RotatePoint(CustomVector2f point, CustomVector2f origin, float angle)
{
	CustomVector2f vecDirec = point - origin;
	float length = vecDirec.GetMagnitude();
	float baseAngle = vecDirec.GetAngle();

	return Polar2Cart(baseAngle + angle, length) + origin;
}