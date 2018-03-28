#include <iostream>
#include "Reader.h"

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
	}

	//Print out the last element of the data to check it got all of the file
	std::cout << sensor1.back() << std::endl;
	std::cout << sensor2.back() << std::endl;

	std::cin.get();
}