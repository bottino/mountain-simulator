#ifndef DESSINABLE_H
#define DESSINABLE_H
#include <iostream>



class Dessinable {
	public: 
	virtual ~Dessinable();
	virtual void dessine() const = 0;
	int tirage(int, int) const;
	
};

#endif
