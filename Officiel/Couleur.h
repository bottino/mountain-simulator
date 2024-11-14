#include "wxIncludes"
#include <GL/glut.h>
#include <GL/glu.h>

class Couleur {
	public:
	Couleur(double,double,double,double);
	Couleur();
	void setR(double);
	void setG(double);
	void setB(double);
	void setT(double);
	double getR();
	double getG();
	double getB();
	double getT();
	private:
	void normalise();
	double r;
	double g;
	double b;
	double t;
};
