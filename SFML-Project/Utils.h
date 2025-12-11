#pragma once
#include "CustomVector2f.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

using LayerMask = unsigned int;
using Vec2f = CustomVector2f;

enum class CharaType { None, Player, CACEnemy, ShooterEnemy, Bullet, Lighting };
enum class ColorType { None = 0, Red = 1, Blue = 2, Green = 3 ,Yellow = 4};
enum class ShapeType { None, Circle, Rectangle, Convex};

enum CollisionLayer : LayerMask
{
	Layer_None = 0,
	Layer_Player = 1 << 0,
	Layer_Enemy = 1 << 1,
	Layer_BulletEnemy = 1 << 2,
	Layer_BulletPlayer = 1 << 3,
	Layer_Collectible = 1 << 4,
	Layer_All = 0xFFFFFFFF
};

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