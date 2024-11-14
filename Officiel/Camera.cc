#include "Camera.h"
#include <math.h>
#include <GL/glu.h>

#define DEFAULT_R 60
#define DEFAULT_THETA 0.85
#define DEFAULT_PHI 0.78

Camera::Camera()
:rayon(DEFAULT_R), theta(DEFAULT_THETA), phi(DEFAULT_PHI)
{
}

	void Camera::setVue() const {
		gluLookAt(rayon*sin(theta)*cos(phi), rayon*sin(theta)*sin(phi), rayon*cos(theta), 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
		}
	
	void Camera::resetVue() { 
		phi = DEFAULT_PHI;
		rayon = DEFAULT_R;
		theta = DEFAULT_THETA; }
	
	void Camera::setRayon(double r){
		this->rayon = r; } 
	void Camera::setTheta(double t){
		if (t<0.1) {t=0.1;}
		if (t>3) {t=3;}
		this->theta = t;}
	void Camera::setPhi(double p) {
		this->phi = p; }
	
	double Camera::getRayon() {return rayon;}
	double Camera::getTheta() {return theta;}
	double Camera::getPhi() {return phi;}
