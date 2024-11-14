#include "CubeDAir.h"
#include "Ciel.h"
#include <cmath>

bool CubeDAir::etat() const {
	if (PPvap()>Prosee()) {return true;} else {return false;}
}

bool CubeDAir::pleut() {
	if (PPvap()>(Prosee() + 1.)) {return true; tau=tau*95./100.;} else {return false;}
}

int CubeDAir::getx() const {return x;}
int CubeDAir::gety() const {return y;}
int CubeDAir::getz() const {return z;}
double CubeDAir::gettau() const {return tau;}
void CubeDAir::settau(double t) {tau=t;}	
void CubeDAir::setXYZ(int a, int b, int c) {x = a; y=b; z = c;}
void CubeDAir::setBernouilli(double a) {Bernouilli = a;}
void CubeDAir::setvcarre(double a) {vcarre=a;}
void CubeDAir::setv(vector<double> vit) {vitesse = vit;}
double CubeDAir::getvcarre() const {return vcarre;}
vector<double> CubeDAir::getv() const {return vitesse;}
double CubeDAir::Enthalpie() const {return Bernouilli - Physique::g*z - getvcarre()/2.;}
double CubeDAir::Temp() const {return (2./7.) * (Physique::mairsec)*Enthalpie()/(Physique::r);}
double CubeDAir::Pression() const {return (Physique::pinf)*pow((Physique::tempinf),-7./2.)*pow(Temp(),7./2.);}
double CubeDAir::PPvap() const {return (tau)*Pression()/((Physique::meau/Physique::mairsec) + tau);}
double CubeDAir::Prosee() const {return (Physique::pref)*exp(13.96 - (5208./Temp()));}

double CubeDAir::Bernouilli = 0;

void CubeDAir::dessine() const { double a(0); if (etat()) {a=1;} else {a=0;}
			cout << x << " " << y << " " << z << " " << vcarre << " " << Enthalpie() << " " << Temp() 
			<< " " << Pression() << " " << PPvap() << " " << Prosee() << " " << a  << endl;
}

ostream& operator<<(ostream& fout, CubeDAir const& c)  {
	c.dessine();
	return fout;
}
