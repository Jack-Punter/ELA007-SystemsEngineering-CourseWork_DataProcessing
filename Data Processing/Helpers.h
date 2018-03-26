#pragma once
#include <ostream>
#include <string>

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