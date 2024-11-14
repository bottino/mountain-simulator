#ifndef MONTAGNE_H
#define MONTAGNE_H

#include <iostream>
#include "ChaineMontagne.h"
using namespace std;

class Montagne: public ChaineMontagne {
public:	Montagne();
	Montagne(double,double,double,double, double, double, double);
	virtual ~Montagne();
	virtual Montagne* copie() const {return new Montagne(*this);}
	double getX0() const;
	double getY0() const;
	double getH() const;
	double getSx() const;
	double getSy() const;
	virtual void dessine() const;
	double altitude(double, double) const;
	
protected:
	
	double x0;
	double y0;
	double h;
	double sx;
	double sy;
};
	ostream& operator<<(ostream&, Montagne const&);
#endif
