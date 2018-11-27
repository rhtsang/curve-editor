#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "curve.h"

using namespace std;

vector<Curve> readCurves(char* file) {
	vector<Curve> curves;

	ifstream inputFile(file);
	string line;
	int numCurves;

	inputFile >> numCurves;
	getline(inputFile, line);
	getline(inputFile, line);

	for (int i = 0; i < numCurves; i++) {

		int numPoints;
		inputFile >> numPoints;
		getline(inputFile, line);

		vector<Coordinate> coordinates;
		for (int j = 0; j < numPoints; j++) {
			float float_x, float_y;
			string string_x, string_y;
			getline(inputFile, line);
			istringstream coordinate(line);
			getline(coordinate, string_x, ' ');
			getline(coordinate, string_y);
			float_x = stof(string_x);
			float_y = stof(string_y);

			Coordinate coord = { float_x, float_y };
			coordinates.push_back(coord);

		}
		Curve curve = { coordinates };
		curves.push_back(curve);

		getline(inputFile, line);

	}

	return curves;
}

vector<Curve> normalize(vector<Curve> curves) {

	vector<Curve> ndc_curves;

	float x_min = curves.at(0).coordinates.at(0).x;
	float x_max = curves.at(0).coordinates.at(0).x;
	float y_min = curves.at(0).coordinates.at(0).y;
	float y_max = curves.at(0).coordinates.at(0).y;

	for (vector<Curve>::iterator itr = curves.begin(); itr != curves.end(); itr++) {
		for (vector<Coordinate>::iterator itr2 = itr->coordinates.begin(); itr2 != itr->coordinates.end(); itr2++) {
			if (itr2->x < x_min) x_min = itr2->x;
			if (itr2->x > x_max) x_max = itr2->x;
			if (itr2->y < y_min) y_min = itr2->y;
			if (itr2->y > y_max) y_max = itr2->y;
		}
	}

	float delta_x = x_max - x_min;
	float delta_y = y_max - y_min;
	float delta = max(delta_x, delta_y);

	for (vector<Curve>::iterator itr = curves.begin(); itr != curves.end(); itr++) {
		vector<Coordinate> ndc;
		for (vector<Coordinate>::iterator itr2 = itr->coordinates.begin(); itr2 != itr->coordinates.end(); itr2++) {
			float x_ndc = (itr2->x) / delta;
			float y_ndc = (itr2->y) / delta;
			Coordinate coord = { x_ndc, y_ndc };
			ndc.push_back(coord);
		}
		Curve curve = { ndc };
		ndc_curves.push_back(curve);
	}

	return ndc_curves;
}