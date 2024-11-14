#ifndef SYSTEME_H
#define SYSTEME_H

#include "ChampPotentiel.h"
#include "Montagne.h"
#include "ChaineMontagne.h"
#include "Ciel.h"
#include <iostream>
#include "Soleil.h"
#include "Dessinable.h"
#include "Terrain.h"
#include <random>
#include <functional>

class Systeme: public Dessinable {
public:
	Systeme(ChampPotentiel&);
	Systeme(ChampPotentiel&, Ciel const&, bool a = false, bool b = false);
	Systeme(Systeme const&) =  delete;
	Systeme operator=(Systeme const&) = delete;
	~Systeme();
	ChampPotentiel getChampot();
	vector<vector<Terrain*> >* getTerrains();
	void evolue();
	void dessine() const;
	void demarre();
	void descTerrain(ostream&);
	void descMeteo(ostream&);

	
private:
	double gaussienne(double, double);
	void evapotranspiration();
	void avancer_nuage();
	void InitTerrain(double);
	void diffusion_humidite();
	vector<vector<Terrain*> > Grille_Terrain;
	ChampPotentiel* champot;
	Ciel* ciel;
	Soleil* soleil;
	bool diffusion ;
	bool mode_texte;
	vector<vector<vector<double> > > carte;
};
ostream& operator<<(ostream&,Systeme const);

#endif
