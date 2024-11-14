#include "Systeme.h"
#include <GL/glut.h>
#include "Ciel3D.h"
#include "Application.h"

using namespace std;

void Systeme::evolue() {
	double nx((*champot).getNx());
	double ny((*champot).getNy());
	for (int i(1); i<nx; ++i) {
		for (int j(1); j<ny; ++j) {
			(*Grille_Terrain[i][j]).evolue();
		}
	}
	avancer_nuage();
	if (diffusion) {diffusion_humidite();}
	evapotranspiration();
	(*soleil).evolue();

}

void Systeme::demarre() {
	InitTerrain((*(*champot).getMontagne()).getH()-5.0);
	wxGetApp().mixImages("textures/herbe_roche.jpg","textures/fertile2_roche.jpg","textures/roche2.jpg",(*(*champot).getMontagne()).getTexMap());
	(*champot).resolution(2.2621843e-5,5000.,false);
	(*ciel).rafraichir(*champot);
	soleil = new Soleil((*champot).getMontagne(),ciel, 0.0, 0.0,200, 2., 15.0, 15.0);
	(*(*champot).getMontagne()).setSoleil(*soleil);
}

void Systeme::dessine() const {
	if (mode_texte) {cout<<this;}
	else  {
	(*(*champot).getMontagne()).dessine();
	(*ciel).dessine(); 
}

}


void Systeme::avancer_nuage(){
	double nx((*champot).getNx());
	double ny((*champot).getNy());
	double nz((*champot).getNz());
	double lambda((*champot).getLambda());
	CubeDAir* a;
	CubeDAir* b;
	
	for (double x(1); x < nx; ++x) {
		for (double y(1); y < ny; ++y) {
			for (double z(1); z < nz; ++z){
				a = (*ciel).getCube(x,y,z);
				b = (*ciel).precedente(x,y,z, 0.031, lambda);
				if (x != (*b).getx() or y!=(*b).gety() or z!=(*b).getz()) {
					if ((*a).etat()==true and (*b).etat()==false) {(*a).settau((*a).gettau()*98.3/100.);}
					if ((*b).etat()==true and (*a).etat()==false) {(*a).settau((*a).gettau()*105./100.);}
			}
		}
	}
}
}

void Systeme::diffusion_humidite() {

	double nx((*champot).getNx());
	double ny((*champot).getNy());
	double nz((*champot).getNz());
	CubeDAir* a;

	for (double x(1); x < nx; ++x) {
		for (double y(1); y < ny; ++y) {
			for (double z(1); z < nz; ++z){
				a = (*ciel).getCube(x,y,z);
				(*a).settau((*ciel).moyenne(x,y,z));
			}
		}
	}
}
	
void Systeme::evapotranspiration() {
	double nx((*champot).getNx());
	double ny((*champot).getNy());
	double nz((*champot).getNz());
	for (int x(1); x < nx; ++ x) {
		for (int y(1); y < ny; ++y) {
		int z(0.0);
		while((*(*champot).getMontagne()).altitude(x,y)>z and z<nz)
			{++z;}
			if ((*(Grille_Terrain[x][y])).pleut() == false) {
		(*(*ciel).getCube(x,y,z)).settau((*(*ciel).getCube(x,y,z)).gettau()*(1.0 + (*soleil).lumiere(x,y,z)*(*(Grille_Terrain[x][y])).evap()));
	}
		if ((*(*ciel).getCube(x,y,z)).gettau() > 1.0) {(*(*ciel).getCube(x,y,z)).settau(1.0);}
		}
	}
}

Systeme::Systeme(ChampPotentiel &CHAMPOT)
:champot(&CHAMPOT), ciel(new Ciel3D(CHAMPOT))
{}

Systeme::Systeme(ChampPotentiel &CHAMPOT, Ciel const& c, bool a , bool b)
:champot(&CHAMPOT), ciel(c.copie()), diffusion(a), mode_texte(b), carte((*champot).getNx()-1., vector<vector<double> >((*champot).getNy()-1., vector<double>(3,0.)))
{
}

Systeme::~Systeme() {
	double nx((*champot).getNx());
	double ny((*champot).getNy());
	for (int i(1); i<nx; ++i) {
		for (int j(1); j<ny; ++j) {
			 delete Grille_Terrain[i][j];
			Grille_Terrain[i][j]=nullptr;
			
		}
	}
}
			
			

ChampPotentiel Systeme::getChampot() {
	return (*champot);}

vector<vector<Terrain*> >* Systeme::getTerrains() { return &Grille_Terrain;}

void Systeme::InitTerrain(double zmax) {
	double nx((*champot).getNx());
	double ny((*champot).getNy());
	double u(0.0);
	double z(0.0);
	double z2(0.0);
	double z3(0.0);
	double z4(0.0);
	
	//vector<vector<vector<double> > > tab(nx-1, vector<vector<double> >(ny-1, vector<double>(3,0.)));
	//carte = tab;
	Grille_Terrain.resize(nx);
	for (int x(1); x < nx; ++ x) {
		Grille_Terrain[x].resize(ny);
		for (int y(1); y < ny; ++y) {
			z = (*(*champot).getMontagne()).altitude(x,y);
			z2= (*(*champot).getMontagne()).altitude(x-1,y);
			z3= (*(*champot).getMontagne()).altitude(x-1,y-1);
			z4= (*(*champot).getMontagne()).altitude(x,y-1);
			double z1((z+z3)/2.);
			Sapin sapin(x-1,y-1,z3,z4,z,z2,tirage(0,100)/100.,tirage(0,100)/100.,0.0); 	
			if (x==1 or y==1 or x == nx-1 or y==ny-1) {
				Grille_Terrain[x][y] = new Fertile(x,y,z,gaussienne(0.7,0.05), ciel,sapin, this->Grille_Terrain);
				carte[x-1][y-1][0] = 1.0;
				carte[x-1][y-1][1] = 0.0;
				carte[x-1][y-1][2] = 0.0;
			}
			else {
				if (z1 > zmax) {
					Grille_Terrain[x][y]= new Roche(x,y,z,gaussienne(0.3,0.01),ciel,sapin, this->Grille_Terrain);
					carte[x-1][y-1][0] = 0.0;
					carte[x-1][y-1][1] = 0.0;
					carte[x-1][y-1][2] = 1.0;
				}
				else {
					u = tirage(0.0,1.0);
					if (u < 1 - sqrt(2*z1/zmax - z1*z1/(zmax*zmax))) {
						Grille_Terrain[x][y] = new Fertile(x,y,z,gaussienne(0.7,0.05), ciel,sapin, this ->Grille_Terrain);
						carte[x-1][y-1][0] = 1.0;
						carte[x-1][y-1][1] = 0.0;
						carte[x-1][y-1][2] = 0.0;
					}
					else if (u < 2 - sqrt(2*z1/zmax - z1*z1/(zmax*zmax)) - sqrt(1-z*z/(zmax*zmax))) {
						Grille_Terrain[x][y] = new Roche(x,y,z,gaussienne(0.3,0.01), ciel,sapin, this->Grille_Terrain);
						carte[x-1][y-1][0] = 0.0;
						carte[x-1][y-1][1] = 0.0;
						carte[x-1][y-1][2] = 1.0;
					}
					else {
						Grille_Terrain[x][y] = new Aride(x,y,z,gaussienne(0.5,0.03),ciel,sapin, this->Grille_Terrain);
						carte[x-1][y-1][0] = 0.0;
						carte[x-1][y-1][1] = 1.0;
						carte[x-1][y-1][2] = 0.0;
					}
				}
			}
		}
	}
	
	(*(*champot).getMontagne()).setGrille(&Grille_Terrain);
	(*(*champot).getMontagne()).setTexMap(carte);
}


ostream& operator<<(ostream& fout, Systeme& systeme) {
	fout << "Le système est constitué de :\n\n";
	fout << (*systeme.getChampot().getMontagne());
	fout << "un champ de potentiels :\n";
	fout << "Nombre de cubes : "<<systeme.getChampot().getNx()<<"x"<<systeme.getChampot().getNy()<<"x"<<systeme.getChampot().getNz()<<"\n";
	fout << "Echelle : "<<systeme.getChampot().getLambda()<<"\n";
	systeme.descTerrain(fout);
	systeme.descMeteo(fout);
	return fout;
}

void Systeme::descTerrain(ostream& fout) {
	int fertile(0);
	int aride(0);
	int roche(0);
	for (size_t x(0); x<carte.size(); ++x) {
		for (size_t y(0); y<carte[0].size(); ++y) {
			if (carte[x][y][0] == 1) {++fertile;}
			if (carte[x][y][1] == 1) {++aride;}
			if (carte[x][y][2] == 1) {++roche;}
		}
	}
	fout << "\nLe terrain est divisé en " 
	<<fertile<< " zones fertiles, " 
	<<aride<< " zones arides et " 
	<<roche<< " zones rocheuses.\n";
}

void Systeme::descMeteo(ostream& fout) {
	int nuages(0);
	int pluie(0);
	
	for (int x(1); x<(*champot).getNx(); ++x) {
		for (int y(1); y<(*champot).getNy(); ++y) {
			for (int z(1); z<(*champot).getNz(); ++z) {
				if (ciel->etat(x,y,z)) {++nuages;}
				if (Grille_Terrain[x][y]->pleut()) {++pluie;}
			}
		}
	}
	fout << "Des nuages se sont formés dans " <<nuages<< " cubes.\n";
	if (pluie > 0) {
		fout << "Il pleut sur " <<pluie<< " zones de terrain.\n";
	}
	else {fout << "Il ne pleut plus.\n";}
}

double Systeme::gaussienne(double m, double s) {
	random_device rd;
	unsigned int graine(rd());
	default_random_engine generateur(graine);
	normal_distribution<double> normal_dist(m,s);
	auto tirage_loi_gaussienne(bind(normal_dist,generateur));
	return tirage_loi_gaussienne(); 
}


