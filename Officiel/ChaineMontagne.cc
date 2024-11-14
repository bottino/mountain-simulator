#include "ChaineMontagne.h"
#include <vector>
#include <iostream>
#include "Soleil.h"
using namespace std;

ChaineMontagne::ChaineMontagne(double a,double b)
:dimx(a), dimy(b), grille(nullptr), soleil(nullptr)
{}

ChaineMontagne::ChaineMontagne(vector< ChaineMontagne * > a, double ab, double b)
: tab(a), dimx(ab), dimy(b)
{grille = nullptr; soleil=nullptr;}

ChaineMontagne::ChaineMontagne(vector< ChaineMontagne * > a, Soleil &s, double ab, double b)
: tab(a), soleil(&s), dimx(ab), dimy(b)
{grille = nullptr;}

ChaineMontagne::~ChaineMontagne()
{delete soleil;}
 
void ChaineMontagne::setSoleil(Soleil& s) {soleil=&s;}
 
void ChaineMontagne::setGrille(vector<vector<Terrain*> >* v) {grille = v; } 

void ChaineMontagne::setTexMap(vector<vector<vector<double> > > const& carte) {texMap = carte;}

double ChaineMontagne::altitude(double x, double y) const{
	double alt(0.0);
	for (size_t i(0); i < tab.size(); ++i) {
		if ((*tab[i]).altitude(x,y)>alt) {alt = (*tab[i]).altitude(x,y);}
	}
	return alt;
}

double ChaineMontagne::getH() const {
	double h(0.0);
	for (size_t i(0); i < tab.size(); ++i) {
		if ((*tab[i]).getH()>h) {h = (*tab[i]).getH();}
	}
	return h; }
	


void ChaineMontagne::dessine() const { 
	for(int x(0); x < dimx; ++x) {
		for (int y(0); y < dimy; ++y) {
			for (int z(0); z <= getH() ; ++z) {
				cout << x << " " << y << " " << altitude(x,y) << endl;
			}
		}
	}
}

void ChaineMontagne::ajoute_montagne(ChaineMontagne const& m) {
	tab.push_back(m.copie());
}

ChaineMontagne ChaineMontagne::getTab(int x) const {return *tab[x];}

void ChaineMontagne::setCouleur(double x,double y,double l) const {
	//glColor3d(l*(*(*grille)[x+1][y+1]).getcouleur().getR(),l*(*(*grille)[x+1][y+1]).getcouleur().getG(),l*(*(*grille)[x+1][y+1]).getcouleur().getB());					
	glColor3d(l,l,l);
}	

ostream& operator<<(ostream& fout, ChaineMontagne const& m)  {
	
	fout << "\nUne chaîne de montagne de dimensions " << m.getDimx() << "et de" << m.getDimy() << ", formée de : \n";
	for (size_t i(0); i<m.getSizeTab(); ++i) {
		fout << "	" << m.getTab(i);
	}
	return fout;
}
