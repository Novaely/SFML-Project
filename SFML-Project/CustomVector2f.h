#pragma once

struct CustomVector2f
{
	float x;
	float y;

	// Constructors
	CustomVector2f();
	CustomVector2f(float _xy);
	CustomVector2f(float _x, float _y);

	// Methods

	float GetSquaredMagnitude() const;
	float GetMagnitude() const;
	CustomVector2f GetNormalised() const;
	CustomVector2f Normalise();
	float GetAngle() const;
	float AngleTo(const CustomVector2f& other) const;
	float SquaredDistanceTo(const CustomVector2f& other) const;
	float DistanceTo(const CustomVector2f& other) const;

	float Dot(const CustomVector2f& other) const;

	// Operators
	CustomVector2f operator+(const CustomVector2f& other) const;
	CustomVector2f operator-(const CustomVector2f& other) const;
	CustomVector2f operator*(const CustomVector2f& other) const;
	CustomVector2f operator/(const CustomVector2f& other) const;

	CustomVector2f& operator+=(const CustomVector2f& other);
	CustomVector2f& operator-=(const CustomVector2f& other);
	CustomVector2f& operator*=(const CustomVector2f& other);
	CustomVector2f& operator/=(const CustomVector2f& other);

	CustomVector2f operator+(const float& other) const;
	CustomVector2f operator-(const float& other) const;
	CustomVector2f operator*(const float& other) const;
	CustomVector2f operator/(const float& other) const;

	CustomVector2f& operator+=(const float& other);
	CustomVector2f& operator-=(const float& other);
	CustomVector2f& operator*=(const float& other);
	CustomVector2f& operator/=(const float& other);

	bool operator==(const CustomVector2f& other) const;
	bool operator!=(const CustomVector2f& other) const;
};