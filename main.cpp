#include <GL/glut.h>
#include <iostream>
#include "curve.h"
#include <vector>
#include "filemanipulation.h"
#include "bezier.h"

using namespace std;

float *PixelBuffer;
vector<Curve> curves;
void display();
int main(int argc, char *argv[])
{
	curves = normalize(readCurves(argv[1]));

	//allocate new pixel buffer, need initialization!!
	PixelBuffer = new float[200 * 200 * 3];

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	//set window size to 200*200
	glutInitWindowSize(200, 200);
	//set window position
	glutInitWindowPosition(100, 100);

	//create and set main window title
	int MainWindow = glutCreateWindow("Project 4: Curve Editor!");
	glClearColor(0, 0, 0, 0); //clears the buffer of OpenGL
	//sets display function
	glutDisplayFunc(display);

	glutMainLoop();//main display loop, will display until terminate
	return 0;

	//cout << argv[1] << endl;
	//cout << curves.size() << endl;
	//for (vector<Curve>::iterator itr = curves.begin(); itr != curves.end(); itr++) {
	//	for (vector<Coordinate>::iterator itr2 = itr->coordinates.begin(); itr2 != itr->coordinates.end(); itr2++) {
	//		cout << itr2->x << ' ' << itr2->y << endl;
	//	}
	//}

	return 0;
}

//main display loop, this function will be called again and again by OpenGL
void display()
{
	//Misc.
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	//draws pixel on screen, width and height must match pixel buffer dimension
	//glDrawPixels(200, 200, GL_RGB, GL_FLOAT, PixelBuffer);

	for (vector<Curve>::iterator itr = curves.begin(); itr != curves.end(); itr++) {
		vector<Coordinate> deCasteljauPoints;
		for (float t = 0.00f; t <= 100.00f; t += 0.01f) {
			Coordinate deCasteljauPoint = deCasteljau(itr->coordinates, t);
			deCasteljauPoints.push_back(deCasteljauPoint);
		}
		glBegin(GL_LINES);
		for (int i = 0; i < deCasteljauPoints.size() - 2; i++) {
			glVertex2f(deCasteljauPoints.at(i).x, deCasteljauPoints.at(i).y);
			glVertex2f(deCasteljauPoints.at(i+1).x, deCasteljauPoints.at(i+1).y);
		}
		glEnd();
	}

	//window refresh
	glFlush();
}
