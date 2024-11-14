#include "Sapin.h"
#include "Application.h"
#include "wxIncludes"
#include <GL/glut.h>


/*
 * Utilisation des sapins:
 * 
 * Tu peux sans autre créer les sapins dans la même double boucle for
 * qui crée la montagne, mais en prenant soin de remettre la texture
 * de la montagne après chaque sapin (on peut peut-être faire un
 * glDeleteTextures, mais j'ai pas testé). Puisque pour l'instant on
 * affiche seulement des couleurs, j'ai pris soin de mettre une texture
 * blanche dans le dossier. Ton code doit ressembler à ça, en changeant
 * les noms. Note que mes textures sont dans un sous-dossier "textures".
 * 
 * 
 * 	glEnable(GL_TEXTURE_2D);
	unsigned int textures[1];											//Pour mettre plus de textures plus tard
	textures[0] = *wxGetApp().getTexture("textures/blanc.jpg",false);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
  	for (x...
 		for (y...
  			glBegin(GL_TRIANGLES);
			glColor3ub(255,255,255);
			
			glTexCoord2f(x/dimx,y/dimy);   //ces lignes disent au programme de plaquer sur ce point telle coordonnée de la texture, entre 0 et 1.
			glVertex3d(x,y,relief[x][y]);
			
			glTexCoord2f((x+1)/dimx,y/dimy);
			glVertex3d(x+1,y,relief[x+1][y]);
			
			glTexCoord2f((x+1)/dimx,(y+1)/dimy);
			glVertex3d(x+1,y+1,relief[x+1][y+1]);
			
			glTexCoord2f(x/dimx,y/dimy);
			glVertex3d(x,y,relief[x][y]);
			
			glTexCoord2f((x+1)/dimx,(y+1)/dimy);
			glVertex3d(x+1,y+1,relief[x+1][y+1]);
			
			glTexCoord2f(x/dimx,(y+1)/dimy);
			glVertex3d(x,y+1,relief[x][y+1]);
			
			glEnd();
			
			 
			Condition de presence de sapin
				Sapin sapin(x, y, relief[x][y], relief[x+1][y], relief[x+1][y+1], relief[x][y+1], delta, epsilon);
				sapin.dessine();
				glBindTexture(GL_TEXTURE_2D, textures[0]);		// /!\ On remet blanc comme texture courante pour ne pas plaquer un sapin sur la montagne
			Fin de la condition
		}
	} 
*/

//Constructeur : les z... correspondent aux altitudes des angles du carré dessiné ci-contre
Sapin::Sapin(double X, double Y, double z1, double z2, double z3, double z4, double DELTA, double EPSILON, double t=0.)							//  (x,y+1)    (x+1,y+1)
: x(X), y(Y), z_xy(z1), z_x1y(z2), z_x1y1(z3), z_xy1(z4), delta(DELTA), epsilon(EPSILON), taille(t)											//     ----------
{}				
																																	//    |          |
																																	//    |          |
void Sapin::dessine() {																												//    |      o   |-             o = sapin
																																	//    |          | ) epsilon
	//glEnable(GL_BLEND);																											//     ---------- -
	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);																				//  (x,y)      (x+1,y)        
																																	//     \delta/	
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *wxGetApp().getTexture("textures/sapin3.png", false));		// Pour une meilleure optimisation, on peut la charger dans montagne, et la binder ici, par un passage en arguemnt. A voir.
	
	glPushMatrix();
	
	//Calcule la hauteur du sapin en fonction de sa position sur le carré
	if (delta > epsilon) {glTranslated(x+delta, y+epsilon, delta*(z_x1y-z_xy)+epsilon*(z_x1y1-z_x1y)+z_xy);}	//Plan (x,y),(x+1,y),(x+1,y+1)
	else {glTranslated(x+delta, y+epsilon, delta*(z_x1y1-z_xy1)+epsilon*(z_xy1-z_xy)+z_xy);}					//Plan (x,y),(x,y+1),(x+1,y+1)
	glScaled(0.9*taille,0.9*taille, 0.9*taille);
	
	for (int i(0); i<180; i+=60) {
		
		glPushMatrix();
		glRotated(i,0.,0.,1.);
		glBegin(GL_QUADS);
		glColor3ub(255,255,255);
		glTexCoord2f(0.0,0.0); glVertex3d(-1.0,0.0,0.0);
		glTexCoord2f(0.0,1.0); glVertex3d(-1.0,0.0,4.0);
		glTexCoord2f(1.0,1.0); glVertex3d(1.0,0.0,4.0);
		glTexCoord2f(1.0,0.0); glVertex3d(1.0,0.0,0.0);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
}
	
void Sapin::setTaille(double a) {
	taille=a;
}
