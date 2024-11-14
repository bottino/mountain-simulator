#include "Montagne3D.h"
#include <GL/glut.h>
#include <cstdlib>
#include "wxIncludes"
#include "Application.h"


using namespace std;

Montagne3D::Montagne3D()
:Montagne()
{}

Montagne3D::Montagne3D(double dimx, double dimy,double a,double b, double c, double d, double e)
:Montagne(dimx,dimy,a,b,c,d,e)
{}



void Montagne3D::dessine() const {
	
	glDepthMask(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_BLEND);
	
	double l(1.0);
	glEnable(GL_TEXTURE_2D);
	unsigned int textures[1];											//Pour mettre plus de textures plus tard
	textures[0] = *wxGetApp().getTexture("textures/blanc.jpg",false);
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, textures[0]);
  	for(int x(0); x < dimx-1.; ++x) {
		for (int y(0); y < dimy-1.; ++y) {
  			glBegin(GL_TRIANGLES);
  			l=(*soleil).lumiere(x,y,altitude (x,y));
  			glColor3d(l*(*(*grille)[x+1][y+1]).getcouleur().getR(),l*(*(*grille)[x+1][y+1]).getcouleur().getG(),l*(*(*grille)[x+1][y+1]).getcouleur().getB());			
			
			glTexCoord2f(x/dimx,y/dimy);   //ces lignes disent au programme de plaquer sur ce point telle coordonnée de la texture, entre 0 et 1.
			glVertex3d(x,y,altitude(x,y));
			
			if (x<28) {l=(*soleil).lumiere(x+1,y,altitude (x+1,y));
				glColor3d(l*(*(*grille)[x+1][y+1]).getcouleur().getR(),l*(*(*grille)[x+1][y+1]).getcouleur().getG(),l*(*(*grille)[x+1][y+1]).getcouleur().getB());			
		}
			
			glTexCoord2f((x+1)/dimx,y/dimy);
			glVertex3d(x+1,y,altitude(x+1,y));
			
			if (x<28 and y<28) {l=(*soleil).lumiere(x+1,y+1,altitude (x+1,y+1));
				glColor3d(l*(*(*grille)[x+1][y+1]).getcouleur().getR(),l*(*(*grille)[x+1][y+1]).getcouleur().getG(),l*(*(*grille)[x+1][y+1]).getcouleur().getB());			
		}
			
			glTexCoord2f((x+1)/dimx,(y+1)/dimy);
			glVertex3d(x+1,y+1,altitude(x+1,y+1));
			
		l=(*soleil).lumiere(x,y,altitude (x,y));
		glColor3d(l*(*(*grille)[x+1][y+1]).getcouleur().getR(),l*(*(*grille)[x+1][y+1]).getcouleur().getG(),l*(*(*grille)[x+1][y+1]).getcouleur().getB());			
				
			glTexCoord2f(x/dimx,y/dimy);
			glVertex3d(x,y,altitude(x,y));
			
			if (x<28 and y<28) {l=(*soleil).lumiere(x+1,y+1,altitude (x+1,y+1));
				glColor3d(l*(*(*grille)[x+1][y+1]).getcouleur().getR(),l*(*(*grille)[x+1][y+1]).getcouleur().getG(),l*(*(*grille)[x+1][y+1]).getcouleur().getB());			
		}
			
			glTexCoord2f((x+1)/dimx,(y+1)/dimy);
			glVertex3d(x+1,y+1,altitude(x+1,y+1));
			
			if (y<28) {l=(*soleil).lumiere(x,y+1,altitude (x,y+1));
				glColor3d(l*(*(*grille)[x+1][y+1]).getcouleur().getR(),l*(*(*grille)[x+1][y+1]).getcouleur().getG(),l*(*(*grille)[x+1][y+1]).getcouleur().getB());			
		}
			
			glTexCoord2f(x/dimx,(y+1)/dimy);
			glVertex3d(x,y+1,altitude(x,y+1));
			
			glEnd();
			
			if ((*(*grille)[x+1][y+1]).getVegetation() > 0.1) { (*(*grille)[x+1][y+1]).getSapin().dessine(); }
			glBindTexture(GL_TEXTURE_2D, textures[0]);		// /!\ On remet blanc comme texture courante pour ne pas plaquer un sapin sur la montagne
		}
	} 
	glPopMatrix();
}


