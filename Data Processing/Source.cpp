#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include "helpers.h"
#include "Matrix2D.h"
#include "Vec2.h"

/*
http://www.movable-type.co.uk/scripts/latlong.html Used to calculate ratio (width/height) to convert to rectangular grid of GPS from square
Done by the northern most GPS coordinate (accross all GPS devices) as well as the southern, eastern and western most coordinates
Took the middle of the east-west and north-south. Used that middle value of north-south and middle of east-west ± 0.1 to get width
Used that middle value of east-west and middle of north-south ± 0.1 to get height.
width  = 13.46km, height = 22.24km
R = 22.24 / 13.46
*/

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
					{ stod(strLong), stod(strLat) },
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


void main()
{
	std::vector<fileData> sensor1;
	std::vector<fileData> sensor2;
	//Read the 2 data files for the first run into the data files
	try
	{
		sensor1 = Reader("G08_RUN-1.CSV");
		sensor2 = Reader("G14_RUN-1.CSV");
	}
	catch (std::runtime_error e)
	{
		std::cout << e.what() << '\n';
		std::cin.get();
		return;
	}

	//Get the first and last time to the nearest second
	int first_time = std::max(sensor1.front().time, sensor2.front().time);
	int last_time = std::min(sensor1.back().time, sensor2.back().time);

	std::cout << "ft: " << first_time << "\nlt: " << last_time << '\n';

	//Remove all elements with a time unique to that sensor
	auto Predicate = [=](fileData x)
	{
		return (x.time < first_time || x.time > last_time);
	};

	remove_erase_if(sensor1, Predicate);
	remove_erase_if(sensor2, Predicate);

	//Create a vector to store the GPS coordinates of the objects
	//With enough space to store the same number of elements as the sensors
	std::vector<outputData> object_data(sensor1.end() - sensor1.begin());

	//Fill object_data with the calculated coordiantes and the time stamp
	std::transform(
		//Loops over all of the data in sensor1 and sensor2
		sensor1.begin(), sensor1.end(), sensor2.begin(),
		//Ouptuts to object_data
		object_data.begin(),
		//Performs this funcion on each elemnt of sensor1[idx], sensor2[idx]
		[=](fileData s1, fileData s2)
		{
			//Calculate the rectangular grid ratio to compute change of basis matrix
			const double R = 22.24 / 13.46;

			//pre calculate the change of basis vector and its inverse
			const Matrix2D baseChange(1, 0, 0, R);
			const Matrix2D InvBaseChange = baseChange.Inverse();

			//The locations of the 2 sensors
			Vec2 loc1 = s1.coordinate;
			Vec2 loc2 = s2.coordinate;
			
			//Calculate the direction the sensors are facing as vectors by rotatin the north vector
			//Using basis change to account for approximately square GPS grid
			Vec2 dir1 = InvBaseChange * Matrix2D::Rotation(s1.bearing) * baseChange * Vec2(0, 1);
			Vec2 dir2 = InvBaseChange * Matrix2D::Rotation(s2.bearing) * baseChange * Vec2(0, 1);

			//Calculate λ1 and λ2 according to derived simultaneous equation.
			Vec2 Distances = Matrix2D(dir1.GetX(), dir2.GetX(), dir1.GetY(), dir2.GetY()).Inverse() * (loc2 - loc1);
			
			return outputData{ loc1 + Distances.GetX() * dir1, s1.time };
		});

	//Output the calcuated data to the console
	std::copy(object_data.begin(), object_data.end(), std::ostream_iterator<outputData>(std::cout, "\n"));


	std::cin.get();
}