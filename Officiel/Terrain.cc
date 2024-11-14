#include "Terrain.h"
#include "wxIncludes"
#include <GL/glut.h>
#include <GL/glu.h>
#include "Ciel.h"
#include <iostream>
using namespace std;

Terrain::Terrain(int p, int q, int r, double a, Ciel* c, Sapin s, vector<vector<Terrain*> > & g)
:x(p), y(q), z(r),vegetation(a), ciel(c), sapin(s), Grille(&g)
{arrondi(); sapin.setTaille(vegetation);
}

Terrain::~Terrain()
{}

Sapin Terrain::getSapin() {return sapin;}

void Terrain::affiche() {
	cout << x << " " << y << " , vegetation: " << vegetation << endl;
}  

double Terrain::getVegetation() {return vegetation;}
void Terrain::setCouleur(double a, double b, double c, double d) {Couleur x(a,b,c,d); couleur=x;}
Couleur Terrain::getcouleur() {return couleur;}
void Terrain::arrondi() 
{if (vegetation < 0.0) {vegetation = 0.0;} 
 if (vegetation > 1.0) {vegetation = 1.0;}
}

bool Terrain::pleut() {													//on parcourt les cellules situées au dessus du terrain pour voir s'il pleut ou pas
	double altmax((*ciel).getNz());
	for (int h(z); h < altmax; ++h) {
		if ((*ciel).pleut(x,y,h)) {return true;}			
	}
	return false;
}

Aride::Aride(int x, int y, int z, double a, Ciel* c,Sapin s, std::vector<std::vector<Terrain*> > & g)
:Terrain(x,y,z,a,c,s,g)
{setCouleur(1.0*(1-vegetation), 1.0*vegetation,0.0,1.0);}

void Aride::evolue() {
	if (pleut()) {double m((vegetation + (*(*Grille)[x+1][y]).getVegetation() + (*(*Grille)[x][y-1]).getVegetation()+ 
			(*(*Grille)[x-1][y]).getVegetation() + (*(*Grille)[x][y+1]).getVegetation())/5); 
			vegetation += m*0.0075;}   												//s'il pleut, on augmente la vegetation proportionnellement à la moyenne des cases voisines et de la case centrale
	else {vegetation=vegetation/1.005; }											//s'il ne pleut pas, la végétation diminue
	arrondi(); 
	couleur.setR(1.0*(1-vegetation));
	couleur.setG(1.0*(1-vegetation) + vegetation);	
	sapin.setTaille(vegetation);										
}

double Aride::evap() {return  0.00001*vegetation;}

Roche::Roche(int x, int y, int z,double a,Ciel* c,Sapin s, std::vector<std::vector<Terrain*> > & g)
:Terrain(x,y,z,a,c,s,g)
{setCouleur((0.8*(1-vegetation) ),(0.8*(1-vegetation) + vegetation),(0.8*(1-vegetation)) , 1.0);
}

void Roche::evolue() {
	if (pleut()) {vegetation+=0.005;} 													//s'il pleut, la vegetation augmente
	else {vegetation=vegetation/1.01;} 												//s'il ne pleut pas, la végétation diminue
	arrondi();
	couleur.setR(0.8*(1-vegetation) );
	couleur.setG(0.8*(1-vegetation) + vegetation);
	couleur.setB(0.8*(1-vegetation) );
	sapin.setTaille(vegetation);
}

double Roche::evap() {return 0.0;}

Fertile::Fertile(int x, int y, int z,double a, Ciel* c,Sapin s, std::vector<std::vector<Terrain*> > & g)
:Terrain(x,y,z,a,c,s,g)
{setCouleur(0.5,0.4*(1-vegetation) + vegetation,0.2,1.0);}

void Fertile::evolue() {
	if (pleut()) {vegetation = vegetation * 1.005;} //s'il pleut la vegetation augment proportionnellement
	else {vegetation=vegetation/1.001;} //s'il ne pleut pas, la végétation diminue
	arrondi();
	couleur.setG(0.4*(1-vegetation) + vegetation);
	sapin.setTaille(vegetation);
}

double Fertile::evap() {return  0.0001*vegetation;}

