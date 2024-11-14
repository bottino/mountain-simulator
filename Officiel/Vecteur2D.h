#ifndef VECTEUR2D_H
#define VECTEUR2D_H

#include <iostream>

using namespace std;

class Vecteur2D {
	public:
	Vecteur2D();
	Vecteur2D(double, double);
	//Vecteur2D(const Vecteur2D&);
	virtual ~Vecteur2D();
	double getx() const;
	double gety() const;
	void setx(double);
	void sety(double);
	Vecteur2D oppose() const;
	Vecteur2D addition(Vecteur2D) const;
	Vecteur2D soustraction(Vecteur2D) const;
	Vecteur2D multscal(double) const;
	double prodscal(Vecteur2D) const;
	void affiche() const ; 
	bool compare(Vecteur2D) const;
	double carrenorme() const;
	double norme() const;

	//Surcharge des opérateurs

	Vecteur2D operator+(Vecteur2D const&) const;
	Vecteur2D& operator+=(Vecteur2D const&);

	Vecteur2D operator-(Vecteur2D const&) const;
	Vecteur2D& operator-=(Vecteur2D const&);

	double operator*(Vecteur2D const&) const;

	Vecteur2D operator*(double const&) const;	

	private:
		double x;
		double y;
};
	ostream& operator<<(ostream&,Vecteur2D const&);
#endif
