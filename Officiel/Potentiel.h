#ifndef POTENTIEL_H
#define POTENTIEL_H

#include "Vecteur2D.h"

class Potentiel {
	
	public:
	
	double getLaplacienY() const;	
	double getLaplacienZ() const;
	
	void setLaplacienY(double);
	void setLaplacienZ(double);

	double getPotentielY() const;
	double getPotentielZ() const;
	double getCarrenormeL();
	void setPotentielY(double);
	void setPotentielZ(double);

	private:

	Vecteur2D potentiel;
	Vecteur2D laplacien;

};

#endif		
