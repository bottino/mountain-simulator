#include "MontagneHMB.h"
#include "Application.h"
#include "Sapin.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <GL/glut.h>
#include <vector>

using namespace std;

MontagneHMB::MontagneHMB(double DIMX, double DIMY, double ALTMAX, double DIV)
: ChaineMontagne(DIMX,DIMY), altMax(ALTMAX), div(DIV)
{
	relief.resize(DIMX);
	for (int x(0); x < DIMX; ++x) {
		relief[x].resize(DIMY);
	}
	setAltitude("textures/3030.jpg");
	TexRoche("textures/3030tex.jpg","textures/herbe.jpg","textures/roche2.jpg",1.);
	TexRoche("textures/3030tex.jpg","textures/fertile2.jpg","textures/roche2.jpg",1.);
}

void MontagneHMB::setAltitude(string nomHM) {
	
	wxImageHandler* jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);
	
	wxImage* heightmap = new wxImage(wxString::From8BitData(nomHM.c_str()), wxBITMAP_TYPE_JPEG);

	double altMaxImport(0);
	double multiplicateur(1);
	if (heightmap->GetWidth() == dimx and heightmap->GetHeight() == dimy) {
		for (int y(0);y<dimy;++y) {
			for (int x(0);x<dimx;++x) {
				
				relief[x][y] = heightmap->GetRed(x,y);
				if (altMaxImport<relief[x][y]) {
					altMaxImport=relief[x][y];
				}
			}
		}
	}
	else {cout << "MontagneHMB : erreur : heightmap incompatible" << endl;}
	
	maxHM = altMaxImport;
	
	free(heightmap);
	if (altMaxImport != 0) {
		multiplicateur = altMax/altMaxImport;
		for (int x(0);x<dimx;++x) {
			for (int y(0);y<dimy;++y) {
				relief[x][y] *= multiplicateur;
			}
		}
	}
}

double MontagneHMB::altitude(double x, double y) const {return relief[x][y];}
double MontagneHMB::getH() const {return altMax;}

void MontagneHMB::dessine() const {
	
	double l(1.0);
	glPushMatrix();
	//glTranslated(-dimx/2.,-dimy/2.,0.);
	
	glDepthMask(true);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	unsigned int textures[1];
	textures[0] = *wxGetApp().getTexture("textures/textureMixee.jpg",true);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	
	
	for (double x(0);x<dimx-1;++x) {
		for (double y(0);y<dimy-1;++y) {
			glLineWidth(0.005);
			
			
			//Montagne en fill
			
			glBegin(GL_TRIANGLES);
			
			l=(*soleil).lumiere(x,y,altitude(x,y));
			setCouleur(x,y,l);
			glTexCoord2f(x/dimx,y/dimy);
			glVertex3d(x,y,relief[x][y]);
			
			if (x<28) {
				l=(*soleil).lumiere(x+1,y,altitude(x+1,y));
				setCouleur(x,y,l);}
			glTexCoord2f((x+1)/dimx,y/dimy);
			glVertex3d(x+1,y,relief[x+1][y]);
			
			if (x<28 and y<28) {
				l=(*soleil).lumiere(x+1,y+1,altitude(x+1,y+1));
				setCouleur(x,y,l);}
			glTexCoord2f((x+1)/dimx,(y+1)/dimy);
			glVertex3d(x+1,y+1,relief[x+1][y+1]);
			
			l=(*soleil).lumiere(x,y,altitude(x,y));
			setCouleur(x,y,l);
			glTexCoord2f(x/dimx,y/dimy);
			glVertex3d(x,y,relief[x][y]);
			
			if (x<28 and y<28) {
				l=(*soleil).lumiere(x+1,y+1,altitude(x+1,y+1));
				setCouleur(x,y,l);}
			glTexCoord2f((x+1)/dimx,(y+1)/dimy);
			glVertex3d(x+1,y+1,relief[x+1][y+1]);
			
			if (y<28) {
				l=(*soleil).lumiere(x,y+1,altitude(x,y+1));
				setCouleur(x,y,l);}
			glTexCoord2f(x/dimx,(y+1)/dimy);
			glVertex3d(x,y+1,relief[x][y+1]);
			
			glEnd();
			if ((*(*grille)[x+1][y+1]).getVegetation() > 0.1) { (*(*grille)[x+1][y+1]).getSapin().dessine(); }
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			//showLineStrip(x,y);
		}
	}
	glPopMatrix();
}

void MontagneHMB::showLineStrip(double x,double y) const {
	//Montagne en line strip
			
			glColor3ub(255,0,0);
			glTexCoord2f(15.,15.);
			
			glBegin(GL_LINE_STRIP);
			glVertex3d(x,y,relief[x][y]+0.02);
			glVertex3d(x+1,y,relief[x+1][y]+0.02);
			glVertex3d(x+1,y+1,relief[x+1][y+1]+0.02);
			
			glVertex3d(x,y,relief[x][y]+0.02);
			glVertex3d(x+1,y+1,relief[x+1][y+1]+0.02);
			glVertex3d(x,y+1,relief[x][y+1]+0.02);
			glEnd();
}

void MontagneHMB::setTexMap(vector<vector<vector<double> > > const& carte) {
	
	vector<vector<vector<double> > > carte2(div*carte.size(), vector<vector<double> >(div*carte[0].size(), vector<double>(3, 0.)));
	for (int i(0); i<carte.size(); ++i) {
		for (int j(0); j<carte[0].size(); ++j) {
			for (int k1(0); k1<div; ++k1) {
				for (int k2(0); k2<div; ++k2) {
					carte2[div*i+k1][div*j+k2][0] = carte[i][j][0];
					carte2[div*i+k1][div*j+k2][1] = carte[i][j][1];
					carte2[div*i+k1][div*j+k2][2] = carte[i][j][2];
				}
			}
		}
	}
	texMap = carte2;
}

void MontagneHMB::TexRoche(string nomHM, string nom1, string nom2, double taux) {
	
	wxImageHandler* jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);
	
	wxImage* heightmap = new wxImage(wxString::From8BitData(nomHM.c_str()), wxBITMAP_TYPE_JPEG);
	wxImage* image1 = new wxImage(wxString::From8BitData(nom1.c_str()), wxBITMAP_TYPE_JPEG);
	wxImage* image2 = new wxImage(wxString::From8BitData(nom2.c_str()), wxBITMAP_TYPE_JPEG);
	
	int dimx(image1->GetWidth());
	int dimy(image2->GetHeight());
	wxImage resultat(dimx,dimy);
	
	heightmap->Rescale(dimx,dimy,wxIMAGE_QUALITY_HIGH);
	heightmap->Rotate90(true);
	heightmap->Mirror(true);
	
	for (int x(0); x<dimx; ++x) {
		for (int y(0); y<dimy; ++y) {		
			double alt(heightmap->GetRed(x,y)/maxHM);
			vector<double> terrain = {image1->GetRed(x,y), image1->GetGreen(x,y), image1->GetBlue(x,y)};
			vector<double> roche = {image2->GetRed(x,y), image2->GetGreen(x,y), image2->GetBlue(x,y)};
			
			for (int i(0); i<3; ++i) {
				
				terrain[i] = (1-taux*alt)*terrain[i] + (taux*alt)*roche[i];
			}
			resultat.SetRGB(x, y, terrain[0], terrain[1], terrain[2]);
		}
	}
	
	for (int k(1); k<5; ++k) {nom1.pop_back();}
	string nomSortie(nom1 + "_roche.jpg");
	resultat.SaveFile(wxString::From8BitData(nomSortie.c_str()), wxBITMAP_TYPE_JPEG);
	
	free(heightmap);
	free(image1);
	free(image2);
}

ostream& operator<<(ostream& fout, MontagneHMB const& m)  {
	
	fout << "Une montagne générée par carte d'altitude de hauteur maximale " <<m.getAltMax()<< "\n";
	
	return fout;
}
	
	
		
		
		
		
	
	
