// SegmentDistance.cpp : Defines the entry point for the application.
//

#include <geom/point.h>
#include <geom/sector.h>
#include <geom/line.h>
#include <geom/distance.h>
#include "argparse/argparse.hpp"

#include <iostream>
#include <ranges>
#include <cassert>


using point = geom::Point_3D<double>;
using sector = geom::Sector_3D<double>;

double sector_distanse(const point& a, const point& b, const point& c, const point& d) {
	sector l{a, b};
	sector r{c, d};

	return geom::distance(l, r);
}

point from_span(std::span<double> arr) {
	assert(arr.size() == 3);
	return point{arr[0], arr[1], arr[2]};
}

int main(int argc, char *argv[])
{
	argparse::ArgumentParser program("Segments distance");
	program.add_description("Print distance beetween two 3D sectors.");

	program.add_argument("points")
		.help("4 points - boundaries of 2 segments")
		.nargs(4 * 3)
		.scan<'g', double>();
	try {
		program.parse_args(argc, argv);
	} 
	catch (const std::exception& err) {
		std::cerr << err.what() << std::endl;
		std::cerr << program;
		return 1;
	}

	auto points_v = program.get<std::vector<double>>("points");
	auto points = std::span<double>(points_v);

	double distanse = sector_distanse(
		from_span(points.subspan(0, 3)),
		from_span(points.subspan(3, 3)),
		from_span(points.subspan(6, 3)),
		from_span(points.subspan(9, 3))
	);
	
	std::cout << distanse << std::endl;

	return 0;
}
