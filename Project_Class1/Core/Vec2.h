#pragma once
#include<cmath>

//2D vector struct, used for position, velocity, and other 2D vector operations
struct Vec2 {
	float x;
	float y;
	explicit Vec2(float x1 = 0.0f, float y1 = 0.0f)
		:x{ x1 }
		, y{ y1 }
	{
	}

	Vec2 operator+(Vec2 b) const
	{
		return Vec2{ x + b.x ,y + b.y };
	}

	Vec2 operator-(Vec2 b) const
	{
		return Vec2{ x - b.x ,y - b.y };
	}

	Vec2 operator*(float b) const 
	{
		return Vec2{ x * b,y * b };
	}

	Vec2& operator+=(Vec2 b) 
	{
		x += b.x;
		y += b.y;
		return *this;
	}

	float dot(Vec2 b) const
	{
		return(x * b.x + y * b.y );
	}

	float length() const
	{
		return(std::sqrt(x * x + y * y));
	}

	void normalize() 
	{
		float len = this->length();
		constexpr float precision{ 1e-6f };// Floating-point precision error guard
		if (len > precision)
		{ 
			float invLen = 1.0f / len; 
			x *= invLen;
			y *= invLen;
		}
		else {
			x = y = 0.0f; 
		}
	}

	Vec2 normalized() const
	{
		Vec2 temp{*this};
		temp.normalize();
		return temp;
	}
};