#include "Couleur.h"

using namespace std;

Couleur::Couleur(double a,double b,double c,double d)
:r(a),g(b),b(c),t(d)
{normalise();}

Couleur::Couleur()
:r(0.6),g(0.6),b(0.6),t(1.0)
{}

void Couleur::normalise() {
	if (r<0.0) {r=0.0;} 
	if (g<0.0) {g=0.0;}
	if (b<0.0) {b=0.0;}
	if (t<0.0) {t=0.0;}
	if (r>1.0) {r=1.0;}
	if (g>1.0) {g=1.0;}
	if (b>1.0) {b=1.0;}
	if (t>1.0) {t=1.0;}
}

void Couleur::setR(double x) {r=x; normalise();}
void Couleur::setG(double x) {g=x; normalise();}
void Couleur::setB(double x) {b=x; normalise();}
void Couleur::setT(double x) {t=x; normalise();}
double Couleur::getR() {return r;}
double Couleur::getG() {return g;}
double Couleur::getB() {return b;}
double Couleur::getT() {return t;}
