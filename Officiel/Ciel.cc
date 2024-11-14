#include "Ciel.h"
#include "constantes.h"
#include <vector>
#include <cmath>
using namespace std;

Ciel::~Ciel()
{}

Ciel::Ciel(ChampPotentiel &champot)
:nx(champot.getNx()), ny(champot.getNy()), nz(champot.getNz()),lambda(champot.getLambda()), vinf(champot.getvinf())
{	tab.resize(nx);
	for(int x(0); x < nx; ++x) {
		tab[x].resize(ny);
		for(int y(0); y < ny; ++y) 
		{tab[x][y].resize(nz); 
	}
}	CubeDAir::setBernouilli(champot.getvinf()*champot.getvinf()/2 + Physique::entinf);

	for(int x(1); x < nx; ++ x) {
		for(int y(1); y <ny; ++y) {
			for(int z(1); z<nz; ++z) {
				tab[x][y][z].setvcarre(champot.carrevitesse(champot.vitesse(x,y,z)));
				tab[x][y][z].setv(champot.vitesse(x,y,z));
				tab[x][y][z].setXYZ(x,y,z);	
				tab[x][y][z].settau(Physique::tau);		
		}
		}
	}
}		


void Ciel::rafraichir(ChampPotentiel& champot) {
	for(int x(1); x < nx; ++ x) {
		for(int y(1); y <ny; ++y) {
			for(int z(1); z<nz; ++z) {
				tab[x][y][z].setvcarre(champot.carrevitesse(champot.vitesse(x,y,z)));
				tab[x][y][z].setv(champot.vitesse(x,y,z));	
		}
	}
}
}
	

Ciel::Ciel(ChampPotentiel &champot, double v)
:nx(champot.getNx()), ny(champot.getNy()), nz(champot.getNz()), lambda(champot.getLambda()), vinf(v)
{	tab.resize(nx);
	for(int x(0); x < nx; ++x) {
		tab[x].resize(ny);
		for(int y(0); y < ny; ++y) 
		{tab[x][y].resize(nz); 
	}
}
	CubeDAir::setBernouilli(champot.getvinf()*champot.getvinf()/2 + Physique::entinf);
	for(int x(1); x < nx-1; ++ x) {
		for(int y(1); y <ny-1; ++y) {
			for(int z(1); z<nz-1; ++z) {
				tab[x][y][z].setvcarre(v);
				tab[x][y][z].setXYZ(x,y,z); tab[x][y][z].settau(Physique::tau);	
			}
		}
	}		
}


CubeDAir* Ciel::precedente(double x,double y,double z,double dt, double lambda) {
	int dx(trunc(-dt*(tab[x][y][z].getv())[0]/lambda));
	int dy(trunc(-dt*(tab[x][y][z].getv())[1]/lambda));
	int dz(trunc(-dt*(tab[x][y][z].getv())[2]/lambda));
	
	int x2(x+dx);
	int y2(y+dy);
	int z2(z+dz);
	
	if (x2 < 1) {x2=1;} ; if (x2 > nx-2) {x2=nx-2;} ;if (y2 < 1) {y2=1;} ; if (y2 > ny-2) {y2=ny-2;};
	if (z2 < 1) {z2=1;} ; if (z2 > nz-2) {z2 = nz-2;};
	
	return &tab[x2][y2][z2];
};

CubeDAir* Ciel::suivante(double x,double y,double z,double dt, double lambda) {
	int dx(trunc(dt*(tab[x][y][z].getv())[0]/lambda));
	int dy(trunc(dt*(tab[x][y][z].getv())[1]/lambda));
	int dz(trunc(dt*(tab[x][y][z].getv())[2]/lambda));
	
	int x2(x+dx);
	int y2(y+dy);
	int z2(z+dz);
	
	if (x2 < 1) {x2=1;} ; if (x2 > nx-2) {x2=nx-2;} ;if (y2 < 1) {y2=1;} ; if (y2 > ny-2) {y2=ny-2;};
	if (z2 < 1) {z2=1;} ; if (z2 > nz-2) {z2 = nz-2;};
	
	return &tab[x2][y2][z2];
};

double Ciel::moyenne(double x,double y, double z) {
	double moyenne(0.0);
	double alpha(0.85);

	double x2( (*precedente(x,y,z,0.031,lambda)).getx());
	double y2( (*precedente(x,y,z,0.031,lambda)).gety());
	double z2( (*precedente(x,y,z,0.031,lambda)).getz());
	double x3((*suivante(x,y,z,0.031,lambda)).getx());
	double y3 ((*suivante(x,y,z,0.031,lambda)).gety());
	double z3((*suivante(x,y,z,0.031,lambda)).getz());

	double tau1(alpha*(tab[x2][y][z]).gettau());
	double tau2(alpha*(tab[x][y2][z]).gettau());
	double tau3(alpha*(tab[x][y][z2]).gettau());
	double tau4(alpha*(tab[x][y2][z2]).gettau());
	double tau5(alpha*(tab[x2][y][z2]).gettau());
	double tau6(alpha*(tab[x2][y2][z]).gettau());
	double tau7(alpha*(tab[x2][y2][z2]).gettau());
	
	double tau8((1-alpha)*(tab[x3][y][z]).gettau());
	double tau9((1-alpha)*(tab[x][y3][z]).gettau());
	double tau10((1-alpha)*(tab[x][y][z3]).gettau());
	double tau11((1-alpha)*(tab[x][y3][z3]).gettau());
	double tau12((1-alpha)*(tab[x3][y][z3]).gettau());
	double tau13((1-alpha)*(tab[x3][y3][z]).gettau());
	double tau14((1-alpha)*(tab[x3][y3][z3]).gettau());
	
	if (x2 == 1 or x2 == nx-1) {tau1 = 0; tau5=0; tau6 =0; tau7=0;}
	if (y2 == 1 or y2 == ny-1) {tau2 = 0; tau4=0; tau6 =0; tau7=0;}	
	if (z2 == 1 or z2 == nz-1) {tau3 = 0; tau4=0; tau5 =0; tau7=0;}	
	if (x3 == 1 or x3 == nx-1) {tau8 = 0; tau12=0; tau13 =0; tau14=0;}
	if (y3 == 1 or y3 == ny-1) {tau9 = 0; tau11=0; tau13 =0; tau14=0;}
	if (z3 == 1 or z3 == nz-1) {tau10 = 0; tau11=0; tau12 =0; tau14=0;}
	
	moyenne = (tau1 +tau2 + tau3 + tau4+tau5+tau6+tau7+tau8+tau9+tau10+tau11+tau12+tau13+tau14)/7.;
		
	return moyenne;	
	
	}

bool Ciel::etat(double x,double y,double z) const {return (tab[x][y][z]).etat();}
bool Ciel::pleut(int x, int y, int z) {return (tab[x][y][z]).pleut();}
double Ciel::getvcarre(double x,double y,double z) {return tab[x][y][z].getvcarre();}
double Ciel::getEnthalpie(double x,double y,double z) {return tab[x][y][z].Enthalpie();}
double Ciel::getTemp(double x,double y,double z) {return tab[x][y][z].Temp();}
double Ciel::getPression(double x,double y,double z) {return tab[x][y][z].Pression();}
double Ciel::getPPvap(double x,double y,double z) {return tab[x][y][z].PPvap();}
double Ciel::getProsee(double x, double y, double z) {return tab[x][y][z].Prosee();}
double Ciel::getvinf() {return vinf;}
int Ciel::getNz() {return nz;}
int Ciel::getNy() {return ny;}
int Ciel::getNx() {return nx;}

CubeDAir* Ciel::getCube(double x, double y, double z)  {return &tab[x][y][z];}

void Ciel::dessine() const {
	for(int x(1); x < nx; ++x) {
		for (int y(1); y < ny; ++y) {
			for (int z(1); z < nz ; ++z) {
				tab[x][y][z].dessine();
			}
		}
	}
}


