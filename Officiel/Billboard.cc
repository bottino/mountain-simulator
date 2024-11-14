#include "Billboard.h"
#include "Application.h"
#include <cmath>
#include <GL/glut.h>

using namespace std;

Billboard::Billboard(double X, double Y, double Z, vector<double> NUM)
: x(X), y(Y), z(Z), numero(NUM)
{}

void Billboard::dessine() {
	
	float matrice[16];
	
	glPushMatrix();
	glTranslated(x-0.5,y-0.5,z+0.5+numero[3]);
	glGetFloatv(GL_MODELVIEW_MATRIX , matrice);

	for( int i(0); i<3; ++i ) {
		for( int j(0); j<3; ++j ) {
			if (i==j) {matrice[4*i+j]=1.;}
			else {matrice[4*i+j]=0.;}
		}
	}
	glLoadMatrixf(matrice);

	glScaled(1.5+numero[1],1.5+numero[2],0.);
	glColor3ub(255,255,255);
	int nombre(numero[0]);
	
	switch (nombre) {
		case 0:
			glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0); glVertex3d(-1.0,-1.0,0);
			glTexCoord2f(0.25,0.0); glVertex3d(1.0,-1.0,0);
			glTexCoord2f(0.25,0.5); glVertex3d(1.0,1.0,0);
			glTexCoord2f(0.0,0.5); glVertex3d(-1.0,1.0,0);
			glEnd();
			break;
		case 1:
			glBegin(GL_QUADS);
			glTexCoord2f(0.5,0.5); glVertex3d(-1.0,-1.0,0);
			glTexCoord2f(0.75,0.5); glVertex3d(1.0,-1.0,0);
			glTexCoord2f(0.75,1.0); glVertex3d(1.0,1.0,0);
			glTexCoord2f(0.5,1.0); glVertex3d(-1.0,1.0,0);
			glEnd();
			break;
		case 2:
			glBegin(GL_QUADS);
			glTexCoord2f(0.5,0.0); glVertex3d(-1.0,-1.0,0);
			glTexCoord2f(0.75,0.0); glVertex3d(1.0,-1.0,0);
			glTexCoord2f(0.75,0.5); glVertex3d(1.0,1.0,0);
			glTexCoord2f(0.5,0.5); glVertex3d(-1.0,1.0,0);
			glEnd();
			break;
		case 3:
			glBegin(GL_QUADS);
			glTexCoord2f(0.75,0.0); glVertex3d(-1.0,-1.0,0);
			glTexCoord2f(1.0,0.0); glVertex3d(1.0,-1.0,0);
			glTexCoord2f(1.0,0.5); glVertex3d(1.0,1.0,0);
			glTexCoord2f(0.75,0.5); glVertex3d(-1.0,1.0,0);
			glEnd();
			break;
		case 4:
			glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.5); glVertex3d(-1.0,-1.0,0);
			glTexCoord2f(0.25,0.5); glVertex3d(1.0,-1.0,0);
			glTexCoord2f(0.25,1.0); glVertex3d(1.0,1.0,0);
			glTexCoord2f(0.0,1.0); glVertex3d(-1.0,1.0,0);
			glEnd();
			break;
		case 5:
			glBegin(GL_QUADS);
			glTexCoord2f(0.25,0.5); glVertex3d(-1.0,-1.0,0);
			glTexCoord2f(0.5,0.5); glVertex3d(1.0,-1.0,0);
			glTexCoord2f(0.5,1.0); glVertex3d(1.0,1.0,0);
			glTexCoord2f(0.25,1.0); glVertex3d(-1.0,1.0,0);
			glEnd();
			break;
		default:
			glBegin(GL_QUADS);
			glTexCoord2f(0.75,0.5); glVertex3d(-1.0,-1.0,0);
			glTexCoord2f(1.0,0.5); glVertex3d(1.0,-1.0,0);
			glTexCoord2f(1.0,1.0); glVertex3d(1.0,1.0,0);
			glTexCoord2f(0.75,1.0); glVertex3d(-1.0,1.0,0);
			glEnd();
	}

	glPopMatrix();
	
}
