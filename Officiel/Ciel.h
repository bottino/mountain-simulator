#ifndef CIEL_H
#define CIEL_H

#include "ChampPotentiel.h"
#include "CubeDAir.h"
#include "Dessinable.h"
#include <vector>


class Ciel: public Dessinable {

public:
	Ciel(ChampPotentiel&);
	Ciel(ChampPotentiel&, double);
	virtual ~Ciel();
	virtual Ciel* copie() const = 0;
	CubeDAir* getCube(double,double,double);
	bool etat(double, double, double) const;
	bool pleut(int,int,int);
	double getvcarre(double,double,double);
	double getEnthalpie(double,double,double);
	double getTemp(double,double,double);
	double getPression(double,double,double);
	double getPPvap(double,double,double);
	double getProsee(double,double,double);
	double getvinf();
	int getNz();
	int getNy();
	int getNx();
	double moyenne(double ,double ,double);
	CubeDAir* precedente(double,double,double,double, double);
	CubeDAir* suivante(double,double,double,double, double);
	void rafraichir(ChampPotentiel&);
	virtual void dessine() const;
	
	protected:
	int nx;
	int ny;
	int nz;
	vector<vector<vector<CubeDAir> > > tab;
	double lambda;
	double const vinf;
	
};

#endif
