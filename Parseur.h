#ifndef PARSEUR_H
#define PARSEUR_H

#include <string>
#include <stack>

using namespace std;

enum Balise {$invalid, $ChaineMontagne, $ChaineMontagne3D, $Montagne, $Montagne3D, $MontagneHMB, $Ciel, $Ciel3D, $ChampPotentiel, $Dimensions, $Lambda, $Epsilon,
				$Systeme, $Vinf, $SousDivisions, $Centre, $Altitude, $Etalement};

//Ces structures contiennent les atributs utiles au constructeur des différentes classes

struct Montagne_att {
	double x0=15;
	double y0=15;
	double h=15;
	double sx=5;
	double sy=5;
	bool init=false;
};

struct MontagneHMB_att {
	//dimx et dimy sont données par le ChampPotentiel
	double altMax=15;
	double div=3;
	bool init=false;
};

struct ChampPotentiel_att {
	int nx;
	int ny;
	int nz;
	double lambda;
	double epsilon;
	double vinf;
	bool init=false;
};



class Parseur {
public:
	Parseur(bool VERB=false);
	void extraire(string);
	
	int ligne;
	stack<string> acces;

	void analyse(ifstream&);
	void extraireInfo(ifstream&);
	void lireBalise(ifstream&);
	char lire(ifstream&,bool espaces=false);
	void reculer(ifstream&);
	double lireNombre(ifstream&);
private:
	string nomFichier;
	bool verbose;
	
	string nomBalise(ifstream&,bool espaces=false);
	void erreur(string,ifstream&);
	Balise convertBalise(string,ifstream&);
	void testBalise(string,ifstream&,bool fermee=false);
	bool testPrecedente(string);
	
	Montagne_att montagne;
	MontagneHMB_att montagneHMB;
	ChampPotentiel_att champot;
};

#endif




