#include "Helpers.h"

//Insertion operator implementations
std::ostream& operator<<(std::ostream& cout, const Matrix2D& rhs)
{
	return cout << '\n' << rhs.r0c0 << "  " << rhs.r0c1 << '\n' << rhs.r1c0 << "  " << rhs.r1c1;
}

std::ostream& operator<<(std::ostream& cout, const Vec2& rhs)
{
	return cout << rhs.GetX() << ',' << rhs.GetY();
}

std::ostream& operator<<(std::ostream& cout, const fileData& data)
{
	return cout << "Longitude; " << data.coordinate.GetX() << "\nLatitude: " << data.coordinate.GetY() << "\nBearing: " << data.bearing << "\nTime: " << data.time << std::endl;
}

std::ostream& operator<<(std::ostream& cout, const outputData& rhs)
{
	return cout << rhs.loc << ',' << rhs.time;
}
