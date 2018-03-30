#pragma once

class Vec2
{
public:
	Vec2() = default;
	Vec2(double x, double y);
	Vec2 operator+(const Vec2& rhs) const;
	Vec2 operator-(const Vec2& rhs) const;
	double GetX() const;
	double GetY() const;
private:
	double x, y;
};

Vec2 operator*(double lhs, const Vec2& rhs);
