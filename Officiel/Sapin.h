#ifndef SAPIN_H
#define SAPIN_H

class Sapin {
public:
	Sapin(double,double,double,double,double,double,double,double,double);
	void dessine();
	int tirage(int,int);
	void setTaille(double);
private:
	double x;
	double y;
	double z_xy;
	double z_x1y;
	double z_x1y1;
	double z_xy1;
	double delta;
	double epsilon;
	double taille;
};

#endif
