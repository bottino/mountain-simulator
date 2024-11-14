#ifndef BILLBOARD_H
#define BILLBOARD_H

#include <vector>
#include <string>
#include "Camera.h"
using namespace std;

class Billboard {
public:
	Billboard(double X, double Y, double Z, vector<double> NUM);
	void dessine();
private:
	double x;
	double y;
	double z;
	vector<double> numero;
};

#endif
