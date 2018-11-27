#include <vector>
#include "curve.h"
#include <iostream>

using namespace std;

//TODO: handle special cases: vertical lines, and maybe horizontal lines?

Coordinate deCasteljau(vector<Coordinate> coordinates, float t) {
	vector<Coordinate> currentPoints = coordinates;
	for (int j = 1; j < coordinates.size(); j++) {
		vector<Coordinate> nextGenPoints;
		for (int i = 0; i < coordinates.size() - j; i++) {
			float nextX = ((1 - t) * currentPoints.at(i).x) + (t * currentPoints.at(i + 1).x);
			float nextY = ((1 - t) * currentPoints.at(i).y) + (t * currentPoints.at(i + 1).y);
			Coordinate coord = { nextX, nextY };
			nextGenPoints.push_back(coord);
		}
		currentPoints = nextGenPoints;
//cout << currentPoints.size() << endl;
//fflush(stdout);
	}

//cout << "currentPoints.size() should be 1? " << currentPoints.size() << endl;
//fflush(stdout);

	return currentPoints.at(0);
}