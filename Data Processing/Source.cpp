#include <iostream>
#include "helpers.h"
#include "Reader.h"
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

	//Fill the dat
	std::transform(
		sensor1.begin(), sensor1.end(), sensor2.begin(),
		object_data.begin(),
		[=](fileData s1, fileData s2)
		{
			const double R = 22.24 / 13.46;

			Vec2 loc1 = s1.coordinate;

			Vec2 loc2 = s2.coordinate;
			
			Matrix2D baseChange(1, 0, 0, R);
			Matrix2D InvBaseChange = baseChange.Inverse();
			
			Vec2 dir1 = InvBaseChange * Matrix2D::Rotation(s1.bearing) * baseChange * Vec2(0, 1);
			Vec2 dir2 = InvBaseChange * Matrix2D::Rotation(s2.bearing) * baseChange * Vec2(0, 1);

			Vec2 Distances = Matrix2D(dir1.GetX(), dir2.GetX(), dir1.GetY(), dir2.GetY()).Inverse() * (loc2 - loc1);
			
			return outputData{ loc1 + Distances.GetX() * dir1, s1.time };
		});

	std::copy(object_data.begin(), object_data.end(), std::ostream_iterator<outputData>(std::cout, "\n"));


	std::cin.get();
}