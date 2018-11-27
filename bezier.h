#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include "curve.h"


Coordinate deCasteljau(vector<Coordinate> coordinates, float t);

#endif // !BEZIER_H
