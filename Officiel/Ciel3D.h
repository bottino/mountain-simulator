#include "Ciel.h"
#include <GL/glu.h>
#include <vector>
class Ciel3D: public Ciel {
	public:
	Ciel3D(ChampPotentiel&);
	Ciel3D(ChampPotentiel&, double);
	virtual ~Ciel3D();
	virtual Ciel3D* copie() const {return new Ciel3D(*this);}
	void dessine() const;
	private:
	GLUquadric* quadrique;
	vector<vector<vector<vector<double> > > > forme;
};
