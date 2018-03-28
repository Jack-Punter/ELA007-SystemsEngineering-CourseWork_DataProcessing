#include <iostream>
#include <assert.h>
#include <ostream>
#include "Reader.h"

std::vector<fileData> Reader(const std::string file)
{
	std::vector<fileData> data;
	//Preallocate 75 entries in the vector
	data.reserve(75);

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
		if (in.good())
		{
			in.getline(&strLat[0], 64, ',');
			in.getline(&strBearing[0], 64, ',');
			in.getline(&strTime[0], 64, '\n');
		}

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
	{
		throw std::runtime_error("Something Got FUCKED");
	}
	//If the eof has been reached we can just return the data
	else if (in.eof())
	{
		return data;
	}
	//If we stopped and none of bad() and eof() there was a fail()
	else if (in.fail())
	{
		throw std::runtime_error("Some kind of fail?");
	}
}

//Insertion operator to allow std::cout to accept fileData structs
std::ostream& operator<< (std::ostream& cout, const fileData& data)
{
	return cout << "Longitude; " << data.longitude << "\nLatitude: " << data.latitude << "\nBearing: " << data.bearing << "\nTime: " << data.time << std::endl;
}
