// SegmentDistance.cpp : Defines the entry point for the application.
//

#include <geom/point.h>
#include <geom/vector.h>

#include <iostream>

using namespace std;

int main()
{
	geom::Point_3D<double> p{ 1, 1, 1 };
	geom::Vector_3D<double> v{ 1, 1, 1 };

	cout << "Hello, segment distance" << endl;
	return 0;
}
