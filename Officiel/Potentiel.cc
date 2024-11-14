#include "Potentiel.h"

	double Potentiel::getLaplacienY() const {return laplacien.getx();} 
	double Potentiel::getLaplacienZ() const {return laplacien.gety();}
	
	void Potentiel::setLaplacienY(double h) {laplacien.setx(h);}
	void Potentiel::setLaplacienZ(double h) {laplacien.sety(h);}

	double Potentiel::getPotentielY() const {return potentiel.getx();}
	double Potentiel::getPotentielZ() const {return potentiel.gety();}
	
	void Potentiel::setPotentielY(double h) {potentiel.setx(h);}
	void Potentiel::setPotentielZ(double h) {potentiel.sety(h);}
	
	double Potentiel::getCarrenormeL() {return laplacien.carrenorme();}
