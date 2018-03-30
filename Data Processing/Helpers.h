#pragma once
#include <ostream>
#include <string>
#include "Matrix2D.h"
#include "Vec2.h"

//Wrapper for std::stod which takes a std::array of chars
//Templated on a size_t so that any size of std::array can be passed
template<size_t S>
inline double stod(std::array<char, S> arr)
{
	return std::stod(std::string(arr.data()));
}

//Wrapper for std::stoi which takes a std::array of chars
//Templated on a size_t so that any size of std::array can be passed
template<size_t S>
inline int stoi(std::array<char, S> arr)
{
	return std::stoi(std::string(arr.data()));
}

template<typename container, typename Pred>
void remove_erase_if(container& c, Pred f)
{
	auto new_end = std::remove_if(c.begin(), c.end(), f);
	c.erase(new_end, c.end());
}

std::ostream& operator<<(std::ostream& cout, const Matrix2D& rhs);
std::ostream& operator<<(std::ostream& cout, const Vec2& rhs);
