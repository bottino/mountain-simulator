#ifndef TERRAIN_H
#define TERRAIN_H
#include <vector>
#include "Couleur.h"
#include "Sapin.h"

class Ciel;

class Terrain {
	
	public:
	Terrain(int, int, int, double,Ciel*, Sapin, std::vector<std::vector<Terrain*> > &);
	virtual void evolue() = 0;
	virtual ~Terrain();
	virtual double evap() = 0;
	double getVegetation();
	Couleur getcouleur() ;
	void affiche();
	Sapin getSapin();
	void setCouleur(double,double,double,double);
	bool pleut();
	protected:
	int x;
	int y;
	int z;
	double vegetation;
	Ciel* ciel;
	Sapin sapin;
	std::vector<std::vector<Terrain*> >* Grille;
	
	void arrondi();
	Couleur couleur;
	
};

class Aride: public Terrain {
	public:
	Aride(int, int, int, double,Ciel*,Sapin, std::vector<std::vector<Terrain*> > &);
	double evap();
	void evolue();
	private:
};

class Roche: public Terrain {
	public:
	Roche(int, int, int, double,Ciel*,Sapin, std::vector<std::vector<Terrain*> > &);
	double evap() ;
	void evolue();
	private:
};
class Fertile: public Terrain {
	public:
	Fertile(int, int, int, double,Ciel*,Sapin, std::vector<std::vector<Terrain*> > &);
	double evap();
	void evolue();
	private:
};

#endif
