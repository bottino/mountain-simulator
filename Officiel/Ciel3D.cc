#include "Ciel3D.h"
#include "Application.h"
#include "Billboard.h"
#include <GL/glu.h>
#include <cstdlib>

using namespace std;

Ciel3D::Ciel3D(ChampPotentiel& c)
:Ciel(c), quadrique(gluNewQuadric())
{
	forme.resize(nx-1);
	for(int x(1); x < nx; ++x) {
		forme[x-1].resize(ny-1);
		for (int y(1); y < ny; ++y) {
			forme[x-1][y-1].resize(nz-1);
			for(int z(1); z < nz; ++z) {
				forme[x-1][y-1][z-1].resize(4);
				double a(rand()%7);
				forme[x-1][y-1][z-1][0]=a;
				double b1((rand()%100)/100.);
				double b2((rand()%100)/100.);
				double b3((rand()%100)/100.);
				forme[x-1][y-1][z-1][1]=b1;
				forme[x-1][y-1][z-1][2]=b2;
				forme[x-1][y-1][z-1][3]=b3;
			}
		}
	}
}

Ciel3D::Ciel3D(ChampPotentiel& c, double d)
:Ciel(c,d), quadrique(gluNewQuadric())
{}

Ciel3D::~Ciel3D()
{gluDeleteQuadric(quadrique);}

void Ciel3D::dessine() const {
	glBindTexture(GL_TEXTURE_2D, *wxGetApp().getTexture("textures/nuages2.png",false));
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDepthMask(false);

	glAlphaFunc(GL_GREATER, 0.0f);	
	for(int x(1); x < nx; ++x) {
		for (int y(1); y < ny; ++y) {
			for(int z(1); z < nz; ++z) {
				if (this->etat(x,y,z)) {
				glLineWidth(0.005);
				
				glPushMatrix();
				Billboard nuage(x,y,z,forme[x-1][y-1][z-1]);
				nuage.dessine();
				glPopMatrix();	
				}
			}
		}
	}
	glDisable(GL_BLEND);
}
