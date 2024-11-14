#ifndef CAMERA_H
#define CAMERA_H

#include "wxIncludes"


class Camera {
public:
	
	Camera();
	
	void setVue() const;
	void resetVue();
	
	void setRayon(double r);
	void setTheta(double t);
	void setPhi(double p);
	
	double getRayon();
	double getTheta();
	double getPhi();
	
private:
	
	double rayon;
	double theta;
	double phi;

} ;

#endif
