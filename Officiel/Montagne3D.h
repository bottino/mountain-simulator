#include "Montagne.h"
#include "Sapin.h"
using namespace std;

class Montagne3D: public Montagne {
	public:
	Montagne3D();
	Montagne3D(double,double,double,double, double, double, double);
	virtual Montagne3D* copie() const {return new Montagne3D(*this);}
	virtual void dessine() const;
	private:

};
