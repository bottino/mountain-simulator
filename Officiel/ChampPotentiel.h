#ifndef CHAMPPOTENTIEL_H
#define CHAMPPOTENTIEL_H

#include <vector>
#include "Potentiel.h"
#include "ChaineMontagne.h"
#include "Montagne.h"

using namespace std;

class ChampPotentiel {
public: 
	ChampPotentiel();
	ChampPotentiel(int, int, int, double, double, ChaineMontagne const&, double);
	virtual void calcule_laplacien() ;
	void affiche_laplaciens() ;
	void affiche_potentiels() ;
	int getNx() const;
	int getNy() const;
	int getNz() const;
	double getLambda() const;
	double getvinf() const;
	double getEpsilon() const;
	ChaineMontagne* getMontagne() const;
	void resolution(double,int,bool);
	vector<double> vitesse(int,int,int);
	double carrevitesse(vector<double>) ;
	void initialise();

private:
	
	void iteration();
	double erreur();
	
	int nx;
	int ny;
	int nz;
	vector<vector<vector<Potentiel> > > champ;
	
	double lambda;
	double epsilon;
	ChaineMontagne* montagne;
	double vinf;
};

#endif
