#pragma once
#include <ostream>
#include <string>
#include "Matrix2D.h"
#include "Vec2.h"

//Struct to store a line of data from the CSV file
struct fileData
{
	Vec2 coordinate;
	double bearing;
	int time;
	//hhmmss -> 142427 = 14:24:27
};

//Struct to store the output data
struct outputData
{
	Vec2 loc;
	int time;
};

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

//Function to quickly remove elements from a vector
//Without having to copy all elements right of the removed object
template<typename container, typename Pred>
void remove_erase_if(container& c, Pred f)
{
	auto new_end = std::remove_if(c.begin(), c.end(), f);
	c.erase(new_end, c.end());
}


//Allows insertions of matrices to output streams (e.g. std::cout)
std::ostream& operator<<(std::ostream& cout, const Matrix2D& rhs);
//Allows insertions of Vectors to output streams (e.g. std::cout)
std::ostream& operator<<(std::ostream& cout, const Vec2& rhs);
//Allows insertions of the input data to output streams (e.g. std::cout)
std::ostream& operator<<(std::ostream& cout, const fileData& data);
//Allows insertions of the output data to output streams (e.g. std::cout)
std::ostream& operator<<(std::ostream& cout, const outputData& rhs);
