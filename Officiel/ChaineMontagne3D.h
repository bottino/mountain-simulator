#ifndef CHAINEMONTAGNE3D_H
#define CHAINEMONTAGNE3D_H

#include "ChaineMontagne.h"
#include <vector>

class ChaineMontagne3D: public ChaineMontagne {
	public:
	ChaineMontagne3D(double,double);
	ChaineMontagne3D(std::vector<ChaineMontagne* >, double, double);
	virtual ChaineMontagne3D* copie() const {return new ChaineMontagne3D(*this);}
	void dessine() const;
};

#endif
