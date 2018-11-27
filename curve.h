#ifndef COORDINATE_H
#define COORDINATE_H

#include <vector>

using namespace std;

struct Coordinate {
public:
	float x;
	float y;
};

struct Curve {
	vector<Coordinate> coordinates;
};

#endif // !1