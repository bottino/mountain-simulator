#include "Montagne.h"
#include <cmath>
#include <iostream>

using namespace std;

#define DEFAULT_X0 0
#define DEFAULT_Y0 0
#define DEFAULT_H 20
#define DEFAULT_SX 29
#define DEFAULT_SY 29

Montagne::Montagne()
: x0(DEFAULT_X0), y0(DEFAULT_Y0), h(DEFAULT_H), sx(DEFAULT_SX), sy(DEFAULT_SY)
{
}
Montagne::Montagne(double dix, double diy, double a, double b, double c, double d, double e)
:ChaineMontagne(dix,diy), x0(a), y0(b), h(c), sx(d), sy(e)
{}
Montagne::~Montagne()
{}

double Montagne::getX0() const {return x0;}
double Montagne::getY0() const {return y0;}
double Montagne::getH() const {return h;}
double Montagne::getSx() const {return sx;}
double Montagne::getSy() const {return sy;}


double Montagne::altitude(double x, double y) const {
	
	double a(h*exp( (-pow(x-x0, 2)/(2*pow(sx, 2))) - (pow(y-y0, 2)/(2*pow(sy, 2))) ) );
	if (a < 0.5) {a=0; return a;}
	else {return a;}
}

void Montagne::dessine() const {
	for(int x(0); x < dimx; ++x) {
		for (int y(0); y < dimy; ++y) {
				cout << x << " " << y << " " << altitude(x,y) << endl;
		}
	}
}

ostream& operator<<(ostream& fout, Montagne const& m)  {
	
	fout << "Une montagne gaussienne de centre (" <<m.getX0()<< "," <<m.getY0()<< "), d'altitude " 
	<<m.getH()<< " et d'étalement " <<m.getSx()<< "x" <<m.getSy()<< ".\n";
	
	return fout;
}
