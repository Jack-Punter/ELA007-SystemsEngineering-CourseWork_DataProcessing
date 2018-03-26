#include "Reader.h"
#include <iostream>
#include <assert.h>
#include <ostream>

std::vector<fileData> Reader(const std::string file)
{
	std::vector<fileData> data;
	//Open an input filestream and checked that the file was successfully opened
	std::ifstream in(file);
	if (!in)
	{
		throw std::runtime_error("Failed to open file");
	}

	//Loop untill you reach the end of the file
	bool done = false;
	while (!done)
	{
		//Arrays to read file data into 
		std::array<char, 64> strLong;
		std::array<char, 64> strLat;
		std::array<char, 64> strBearing;
		std::array<char, 64> strTime;

		//Read a line from the file
		in.getline(&strLong[0], 64, ',');
		in.getline(&strLat[0], 64, ',');
		in.getline(&strBearing[0], 64, ',');
		in.getline(&strTime[0], 64, '\n');

		//If the file stream is still in a good state (not encountered an EOF or error)
		//convert the loaded strings into number values and create a fileData object to put into
		//the data vector
		if (in.good())
		{
			data.push_back(
				fileData{
					stod(strLong),
					stod(strLat),
					stod(strBearing),
					stoi(strTime)
				});
		}
		//If it isn't in a good state exit this loop 
		else
		{
			done = true;
		}
	}

	//Something is really bad like the file was lost after opening (storage drive was removed during reading)
	if (in.bad())
		throw std::runtime_error("Soemthing Got FUCKED");
	//This currently will be true when we reach the end of the file (possibly due to multiple reads after EoF) 
	else if (in.fail())
	{
		std::cout << "Some kind of fail?\nPossibly due to end of last line was end of stream.\n";
	}
}

//Insertion operator to allow std::cout to accept fileData structs
std::ostream& operator<< (std::ostream& cout, const fileData& data)
{
	cout << "Longitude; " << data.longitude;
	cout << "\nLatitude: " << data.latitude;
	cout << "\nBearing: " << data.bearing;
	cout << "\nTime: " << data.time << std::endl;
}
