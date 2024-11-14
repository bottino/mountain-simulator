#ifndef CHAINEMONTAGNE_H
#define CHAINEMONTAGNE_H

#include "Dessinable.h"
#include <vector>
#include <iostream>
#include "Terrain.h"

using namespace std;

class Soleil;

class ChaineMontagne : public Dessinable {
	public:
	ChaineMontagne() = default;
	ChaineMontagne(double,double);
	ChaineMontagne(vector<ChaineMontagne* >, double, double);
	ChaineMontagne(vector<ChaineMontagne* >, Soleil &, double, double);
	virtual ChaineMontagne* copie() const {return new ChaineMontagne(*this);}
	void setSoleil(Soleil &);
	void ajoute_montagne(ChaineMontagne const&);
	virtual ~ChaineMontagne(); 
	size_t getSizeTab() const {return tab.size();}
	virtual double altitude(double, double) const;
	virtual void dessine() const;
	virtual double getH() const;
	void setGrille(vector<vector<Terrain*> >*);
	virtual void setTexMap(vector<vector<vector<double> > > const& );
	vector<vector<vector<double > > > getTexMap() const {return texMap;}
	ChaineMontagne getTab(int x) const;
	double getDimx() const {return dimx;}
	double getDimy() const {return dimy;}
	void setCouleur(double,double,double) const;
	
	protected:
	vector<ChaineMontagne*> tab;
	Soleil* soleil;
	double dimx;
	double dimy;
	vector<vector<Terrain*> >* grille;
	vector<vector<vector<double> > > texMap;
	
};
	ostream& operator<<(ostream&, ChaineMontagne const&);
#endif
