#include "Vecteur2D.h"
#include <cmath>
#include <iostream>

using namespace std;

Vecteur2D::Vecteur2D()
: x(0.0), y(0.0)
{}

Vecteur2D::Vecteur2D(double x0, double y0)
: x(x0), y(y0)
{}

Vecteur2D::~Vecteur2D()
{}

//Vecteur2D::Vecteur2D(const Vecteur2D& v2)
//: x(v2.getx()), y(v2.gety())
//{}



//Méthodes get

double Vecteur2D::getx() const {return x;}
double Vecteur2D::gety() const {return y;}

//Méthodes set

void Vecteur2D::setx(double a) {x=a;}
void Vecteur2D::sety(double b) {y=b;}

//Opérateurs 


	
Vecteur2D Vecteur2D::addition(Vecteur2D v1) const{
	Vecteur2D v2;
	v2.setx(x+v1.getx());
	v2.sety(y+v1.gety());
	return v2;
	}
	
Vecteur2D Vecteur2D::soustraction(Vecteur2D v1) const {
	Vecteur2D v2;
	v2.setx(x-v1.getx());
	v2.sety(y-v1.gety());
	return v2;
	}
	
Vecteur2D Vecteur2D::multscal(double a) const{
	Vecteur2D v2;
	v2.setx(a*x);
	v2.sety(a*y);
	return v2;
}
	
double Vecteur2D::prodscal(Vecteur2D v1) const{
	double z(x*v1.getx()+y*v1.gety());
	return z;
}

void Vecteur2D::affiche() const{ cout  << x << "  " << y ;}

bool Vecteur2D::compare(Vecteur2D v1) const {
	if (x==v1.getx() and y==v1.gety()) {return true;} 
	else {return false;}
}

Vecteur2D Vecteur2D::oppose() const {
	Vecteur2D v1;
	v1.setx(-x);
	v1.sety(-y);
	return v1;
}

double Vecteur2D::carrenorme() const {
	double z;
	z = x*x + y*y;
	return z;
}

double Vecteur2D::norme() const {
	double z;
	z= sqrt(carrenorme());
	return z;
}


//Surcharge des opérateurs 

	Vecteur2D Vecteur2D::operator+(Vecteur2D const& v1) const {
		Vecteur2D z(addition(v1));
		return z;
	}
		
	Vecteur2D&  Vecteur2D::operator+=(Vecteur2D const& v1) {
		(*this) =(*this).addition(v1);
		return *this;
	}

	Vecteur2D Vecteur2D::operator-(Vecteur2D const& v1) const {
		Vecteur2D z(soustraction(v1));
		return z;
	}
		
	Vecteur2D&  Vecteur2D::operator-=(Vecteur2D const& v1) {
		(*this) =(*this).soustraction(v1);
		return *this;
	}
	
	double Vecteur2D::operator*(Vecteur2D const& v2) const {
		double z(prodscal(v2));
		return z;
	}
	
	ostream& operator<<(ostream& fout, Vecteur2D const& v) {
		fout << v.getx() << " " << v.gety() ;
		return fout;
}
	Vecteur2D Vecteur2D::operator*(double const& mu) const {
		Vecteur2D z(multscal(mu));
		return z;
}
	
