#pragma once
#include <ostream>
#include <fstream>
#include <vector>
#include <array>
#include "helpers.h"
#include "Vec2.h"

//Struct to store a line of data from the CSV file
struct fileData
{
	Vec2 coordinate;
	double bearing;
	int time;
	//hhmmss -> 142427 = 14:24:27
};

std::vector<fileData> Reader(const std::string file);

std::ostream& operator<< (std::ostream& cout, const fileData& data);