#include "ChampPotentiel.h"
#include <cmath>
using namespace std;
ChampPotentiel::ChampPotentiel()
: nx(30), ny(30), nz(30), lambda(1)
{}
ChampPotentiel::ChampPotentiel(int a, int b, int c, double d, double e, ChaineMontagne const& m, double v)
: nx(a), ny(b), nz(c), lambda(d), epsilon(e), montagne(m.copie()), vinf(v)
{
initialise();
}

int ChampPotentiel::getNx() const{
	return nx;}
int ChampPotentiel::getNy() const{
	return ny;}
int ChampPotentiel::getNz() const {
	return nz;}
double ChampPotentiel::getLambda() const {
	return lambda;}
double ChampPotentiel::getEpsilon() const { 
	return epsilon;}
ChaineMontagne* ChampPotentiel::getMontagne() const {
	return montagne;}
double ChampPotentiel::getvinf() const {
	return vinf;}



void ChampPotentiel::initialise() {
	double ly((ny-1)*lambda);
champ.resize(nx);
for(int x(0); x < nx; ++x) {
	champ[x].resize(ny);
	for(int y(0); y < ny; ++y) { champ[x][y].resize(nz);}
}	
	for(int x(0); x< nx; ++x) {
		for(int y(0); y<ny; ++y) {
			for(int z(0); z<nz; ++z) {
				if (z<(*montagne).altitude(x, y)) {
					champ[x][y][z].setPotentielY(0.0);
					champ[x][y][z].setPotentielZ(0.0);
				}
				else 
				{
					champ[x][y][z].setPotentielY((-vinf/2.)*(z*lambda));
					champ[x][y][z].setPotentielZ((vinf/2.)*(y*lambda-ly/2.));
				}
			}
		}
	}
}

void ChampPotentiel::calcule_laplacien() {
	double ly;
	double lz;
	for(int x(1); x < nx-1; ++x) {
		for(int y(1); y < ny-1; ++y) {
			for(int z(1); z < nz-1; ++z) {
			if (z >= (*montagne).altitude(x,y)) {
			ly = champ[x-1][y][z].getPotentielY() + champ[x][y-1][z].getPotentielY() + champ[x][y][z-1].getPotentielY() 
			- 6*champ[x][y][z].getPotentielY() + champ[x+1][y][z].getPotentielY() + champ[x][y+1][z].getPotentielY() + champ[x][y][z+1].getPotentielY();
			lz = champ[x-1][y][z].getPotentielZ() + champ[x][y-1][z].getPotentielZ() + champ[x][y][z-1].getPotentielZ() 
			- 6*champ[x][y][z].getPotentielZ() + champ[x+1][y][z].getPotentielZ() + champ[x][y+1][z].getPotentielZ() + champ[x][y][z+1].getPotentielZ();
			champ[x][y][z].setLaplacienY(ly);
			champ[x][y][z].setLaplacienZ(lz);
}
			}
		}
	}
}

void ChampPotentiel::affiche_laplaciens() {
	for(int x(0); x < nx; ++x) {
		for(int y(0); y < ny; ++y) {
			for(int z(0); z < nz; ++z) {
			cout << x << " " << y << " " << z << " " << champ[x][y][z].getLaplacienY() << " " << champ[x][y][z].getLaplacienZ()<< endl;
			}
		}
	}
}

void ChampPotentiel::affiche_potentiels() {
	for(int x(0); x < nx; ++x) {
		for(int y(0); y < ny; ++y) {
			for(int z(0); z < nz; ++z) {
			cout << x << " " << y << " " << z << " " << champ[x][y][z].getPotentielY() << " " << champ[x][y][z].getPotentielZ() <<endl;
			}
		}
	}
}


void ChampPotentiel::iteration() {
	double ly;
	double lz;
	for(int x(1); x < nx-1; ++x) {
		for(int y(1); y < ny-1; ++y) {
			for(int z(1); z < nz-1; ++z) {
				ly = champ[x][y][z].getPotentielY() + epsilon*champ[x][y][z].getLaplacienY();
				lz = champ[x][y][z].getPotentielZ() + epsilon*champ[x][y][z].getLaplacienZ();
				champ[x][y][z].setPotentielY(ly);
				champ[x][y][z].setPotentielZ(lz);	
			}
		}
	}
}

double ChampPotentiel::erreur() {
	double erreur(0.0);
	for(int x(0); x < nx; ++x) {
		for(int y(0); y < ny; ++y) {
			for(int z(0); z < nz; ++z) {
				erreur += champ[x][y][z].getCarrenormeL();
			}
		}
	}
	return erreur;
}

void ChampPotentiel::resolution(double seuil, int maxIter, bool verbose) {
	double error(0.0);
	int iter(0.0);
	do {
		iteration();
		calcule_laplacien();
		++iter;
		error = erreur();
		if (iter%50 == 0) {
			cout << iter << " " << error << endl;
		
		
			if (verbose==true) {
				affiche_potentiels();
				affiche_laplaciens();
			}
		}
	} while (error > seuil and iter < maxIter);
}

vector<double> ChampPotentiel::vitesse(int i,int j, int k) {
	vector<double> v(3);
	if (i==0 or j==0 or k==0 or i==nx-1 or j==ny-1 or k==nz-1) {v[0] = 0.0; v[1] = 0.0; v[2]=0.0;}
	else {
	double xi(champ[i][j+1][k].getPotentielZ()-champ[i][j-1][k].getPotentielZ()
			-champ[i][j][k+1].getPotentielY()+champ[i][j][k-1].getPotentielY());
	double yi(-champ[i+1][j][k].getPotentielZ()+champ[i-1][j][k].getPotentielZ());
	double zi(champ[i+1][j][k].getPotentielY()-champ[i-1][j][k].getPotentielY());
	v[0]=xi/(2*lambda);v[1]=yi/(2*lambda);v[2]=zi/(2*lambda);
}
	return v;
	}
			
double ChampPotentiel::carrevitesse(vector<double> v) {return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];}			
