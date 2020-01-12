#pragma once

namespace Mates
{

	const float   Pi = 3.141592653589793238462643383279502884f;
	const float   TwoPi = Pi * 2;
	const float   HalfPi = Pi / 2;
	const float   QuarterPi = Pi / 4;

	inline float DegsToRads(float degs)
	{
		return TwoPi * (degs / 360.0f);
	}

	inline float RadsToDegs(float rads)
	{
		return (rads*360.0f) / TwoPi;
	}

	inline float Length(sf::Vector2f v) {
		return sqrt(v.x * v.x + v.y*v.y);
	}

	inline float Distance(sf::Vector2f a, sf::Vector2f b)
	{
		return sqrt((b.y - a.y)*(b.y - a.y) + (b.x - a.x)*(b.x - a.x));
	}

	inline sf::Vector2f Normalize(sf::Vector2f v)
	{
		float length = Length(v);
		if (length < 0.001 && length > -0.001) return sf::Vector2f();
		return sf::Vector2f(v.x / length, v.y / length);
	}

	float Lerp(float from, float to, float t)
	{
		if (t > 1) t = 1;
		if (t < -1) t = -1;
		return (from)+(to - from)*t;
	}

	float Clamp(float v, float min, float max)
	{
		if (v > max) {
			return max;
		}
		if (v < min) {
			return min;
		}
		return v;
	}
}
