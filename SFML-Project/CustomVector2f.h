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