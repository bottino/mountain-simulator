#ifndef MONTAGNEHMB_H
#define MONTAGNEHMB_H

#include "wxIncludes"
#include <vector>
#include <string>
#include "ChaineMontagne.h"
using namespace std;

class MontagneHMB: public ChaineMontagne {

public:	
	MontagneHMB(double,double,double,double);
	
	virtual ~MontagneHMB() {}
	virtual MontagneHMB* copie() const {return new MontagneHMB(*this);}
	
	void setAltitude(string);
	double altitude(double,double) const;
	void dessine() const;
	void showLineStrip(double x,double y) const;
	double getH() const;
	void setTexMap(vector<vector<vector<double> > > const& carte);
	void TexRoche(string,string,string,double);
	
	double getAltMax() const {return altMax;}

private:
	vector<vector<double> > relief;
	double altMax;
	double div;
	double maxHM;
};

ostream& operator<<(ostream&, MontagneHMB const&);

#endif
