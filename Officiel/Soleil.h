#ifndef SOLEIL_H
#define SOLEIL_H

#include "Dessinable.h"
#include "Ciel.h"

class Ciel;
class ChaineMontagne;

class Soleil: public Dessinable {
	public:
	Soleil(ChaineMontagne*, Ciel*,double, double, double, double, double, double);
	double lumiere(double,double,double);
	void evolue();
	void dessine() const;
	double getPhi();
	double getTheta();
	double getRayon();
	private:
	ChaineMontagne* montagne;
	Ciel* ciel;
	double phi;
	double theta;
	double d;
	double r;
	double x0;
	double y0;
};

#endif
