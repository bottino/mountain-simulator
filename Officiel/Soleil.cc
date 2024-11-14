#include "Soleil.h"
#include "Ciel.h"
#include "ChaineMontagne.h"
#include "Application.h"
#include "wxIncludes"
#include <cstdlib>
#include <GL/glut.h>
#include <cmath>
#include <iostream>

using namespace std;

Soleil::Soleil(ChaineMontagne* m, Ciel* ci,double a = 0.3, double b = 0.0, double c= 200., double k=2., double x=15., double y=15.)
:montagne(m), ciel(ci), phi(a), theta(b), d(c), r(k), x0(x), y0(y)
{
}

void Soleil::evolue() {theta += 0.01; }
double Soleil::getTheta() {return theta;}
double Soleil::getPhi() {return phi;}
double Soleil::getRayon() {return r;}


double Soleil::lumiere(double x, double y, double z) {
	double l(1.0); 
	double x2(x);
	double y2(y);
	double z2(z);
	int xmax((*ciel).getNx());
	int ymax((*ciel).getNy());
	int zmax((*ciel).getNz());

	double xs(d*cos(theta)*cos(phi)+x0);
	double ys(d*cos(theta)*sin(phi)+y0);		//changement coordonnées
	double zs(d*sin(theta));
	
	double a(xs-x2); double b(ys-y2); double c(zs-z2);				//détermine un vecteur de longueur 1
	double normecarre(a*a + b*b + c*c);
	a= a/sqrt(normecarre);
	b= b/sqrt(normecarre);
	c= c/sqrt(normecarre);
	if (zs <0) {return 0.3;}
	else {
	while(x2>1 and y2>1 and z2>1 and z2<zmax-1 and y2<ymax-1 and x2<xmax-1){
		if ((*ciel).etat(trunc(x2),trunc(y2),trunc(z2))) {l=l*90./100.;}
		x2 += a; y2+=b ; z2+=c;	
		if ((*montagne).altitude(x2,y2) > z2) {return 0.5;}
		
}
	return l;
}

}

void Soleil::dessine() const {
	double x(d*cos(theta)*cos(phi) + x0);
	double y(d*cos(theta)*sin(phi) + y0);
	double z(d*sin(theta));
	glEnable(GL_TEXTURE_2D);
	
	GLUquadric* quadrique= gluNewQuadric();
	glBindTexture(GL_TEXTURE_2D, *wxGetApp().getTexture("textures/soleil.jpg"));
	gluQuadricTexture(quadrique,GL_TRUE);
	gluQuadricDrawStyle(quadrique, GLU_FILL);
	
	glPushMatrix();
	glTranslated(x,y,z);
	gluSphere(quadrique, r,30, 30);
	glPopMatrix();
	gluDeleteQuadric(quadrique); 
	glPopMatrix();
		
	glDisable(GL_TEXTURE_2D);
}
