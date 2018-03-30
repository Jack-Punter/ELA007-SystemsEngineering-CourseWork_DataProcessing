#pragma once
#include "Vec2.h"
class Matrix2D
{
public:
	Matrix2D(double r0c0, double r0c1, 
			 double r1c0, double r1c1);
	Vec2 operator*(const Vec2& lhs) const;
	Matrix2D operator*(const Matrix2D& lhs) const;
	double Det() const;
	Matrix2D Inverse() const;

	double r0c0, r0c1,
		   r1c0, r1c1;
};

Matrix2D operator*(double lhs, const Matrix2D& rhs);