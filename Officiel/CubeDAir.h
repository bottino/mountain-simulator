#ifndef CUBEDAIR_H
#define CUBEDAIR_H

#include <iostream>
#include <vector>
#include "Dessinable.h"
#include "constantes.h"

using namespace std;

class CubeDAir: Dessinable {
	public:
	void settau(double);
	void setXYZ(int, int, int);
	void setvcarre(double);
	void setv(vector<double>);
	void dessine() const;
	
	bool etat() const;
	bool pleut();
	
	int getx() const;
	int gety() const;
	int getz() const;
	double gettau() const;
	vector<double> getv() const;
	double getvcarre() const;
	double Enthalpie() const;
	double Temp() const;
	double Pression() const;
	double PPvap() const;
	double Prosee() const;
	static void setBernouilli(double);
	
	private:
	double tau;
	static double Bernouilli;	
	double vcarre;
	vector<double> vitesse;
	int z;
	int x;
	int y;
};
	ostream& operator<<(ostream&, CubeDAir const&);
#endif
