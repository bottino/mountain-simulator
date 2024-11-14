#include "Parseur.h"
#include <iostream>
#include <fstream>

using namespace std;

Parseur::Parseur(bool VERB)
: ligne(1), verbose(VERB)
{}

void Parseur::extraire(string nomFichier) {
	ifstream fichier;
	fichier.open(nomFichier);
	analyse(fichier);
	
	fichier.close();
	if(verbose) {cout << "Le curseur est à la ligne " << ligne << endl;}
}

void Parseur::analyse(ifstream& fichier) {
	
	char c(lire(fichier));
	if (c == '<') {
		lireBalise(fichier);
	}
	else {
		reculer(fichier);
		extraireInfo(fichier);
	}
}

void Parseur::lireBalise(ifstream& fichier) {
	
	char c(lire(fichier));
	if (c=='/') {
		string nom(nomBalise(fichier));
		testBalise(nom,fichier,true);
		if(acces.top() == nom) {
			acces.pop();
			if (nom != "Systeme") {analyse(fichier);}
		}
		
		else {erreur("Balises croisées", fichier);}
	}
	else if (c=='!') {
		char d(lire(fichier));
		char e(lire(fichier));
		if (d=='-' and e=='-') {
			string comment(nomBalise(fichier,true));
			char f(comment[comment.size()-1]);
			char g(comment[comment.size()-2]);
			if (f=='-' and g=='-') {
				if (verbose) {
					cout << "Ligne " << ligne << " : commentaire : "<< comment.substr(0,comment.size()-2) <<endl;
				}
				analyse(fichier);
			}
			else {erreur("Balise de commentaire mal refermée",fichier);}
		}
		else {erreur("Balise de commentaire mal ouverte",fichier);}
	}
	else {
		reculer(fichier);
		string nom(nomBalise(fichier));
		testBalise(nom,fichier);
		acces.push(nom);
		analyse(fichier);
	}
}
char Parseur::lire(ifstream& fichier, bool espaces) {
	
	char c(fichier.get());
	if (c==' ' or c == '\t' and fichier.eof() == false) {
		if (espaces) {return c;}
		else {lire(fichier);}
	}
	else if (c!=' ' and c != '\n' and c != '\t' and fichier.eof() == false) {
		return c;
	}
	else if (c == '\n' and fichier.eof() == false) {
		++ligne;
		lire(fichier);
	}	
	else {return '\n';}
}

void Parseur::reculer(ifstream& fichier) {
	if (fichier.eof()) {fichier.clear();} //Pour effacer les error flags du ifstream quand il est arrivé au bout du fichier
	fichier.seekg(fichier.tellg()-1);
}

string Parseur::nomBalise(ifstream& fichier, bool espaces) {
	string nom;
	char c(lire(fichier,espaces));
	while (c != '>') {
		nom += c;
		c = lire(fichier,espaces);
	}
	return nom;
}

void Parseur::erreur(string texte, ifstream& fichier) {
	cerr <<"Ligne "<<ligne<<" : erreur : "<<texte<<endl;
	fichier.close();
}

void Parseur::extraireInfo(ifstream& fichier) {
	Balise balise(convertBalise(acces.top(),fichier));
	
	switch (balise) {

		case $SousDivisions :
			montagneHMB.div = lireNombre(fichier);
			break;
		case $Centre :
			if (testPrecedente("Montagne")==true or testPrecedente("Montagne3D")==true) {
				montagne.x0 = lireNombre(fichier);
				montagne.y0 = lireNombre(fichier);}
			else {erreur("Balise mal placée", fichier);}
			break;
		case $Etalement :
			if (testPrecedente("Montagne")==true or testPrecedente("Montagne3D")==true) {
				montagne.sx = lireNombre(fichier);
				montagne.sy = lireNombre(fichier);}
			else {erreur("Balise mal placée", fichier);}
			break;
		case $Altitude :
			if (testPrecedente("Montagne")==true or testPrecedente("Montagne3D")==true) {
				montagne.h = lireNombre(fichier);
			}
			else if (testPrecedente("MontagneHMB")) {
				montagneHMB.altMax = lireNombre(fichier);
			}
			else {erreur("Balise mal placée", fichier);}
			break;
		case $Vinf :
			champot.vinf = lireNombre(fichier);
			break;
		case $Dimensions :
			if (testPrecedente("ChampPotentiel")) {
				champot.nx = lireNombre(fichier);
				champot.ny = lireNombre(fichier);
				champot.nz = lireNombre(fichier);}
			else {erreur("Balise mal placée", fichier);}
			break;
		case $Lambda :
			champot.lambda = lireNombre(fichier);
			break;
		case $Epsilon :
			champot.epsilon = lireNombre(fichier);
			break;
		default :
			testBalise(acces.top(),fichier);
	}
	analyse(fichier);
}

double Parseur::lireNombre(ifstream& fichier) {
	double nombre;
	fichier >> nombre;
	return nombre;
}

Balise Parseur::convertBalise(string nom, ifstream& fichier) {
	
	Balise balise;
	if (nom == "ChaineMontagne") {balise = $ChaineMontagne;}
	else if (nom == "ChaineMontagne3D") {balise = $ChaineMontagne3D;}
	else if (nom == "Montagne") {balise = $Montagne;}
	else if (nom == "Montagne3D") {balise = $Montagne3D;}
	else if (nom == "MontagneHMB") {balise = $MontagneHMB;}
	else if (nom == "Ciel") {balise = $Ciel;}
	else if (nom == "Ciel3D") {balise = $Ciel3D;}
	else if (nom == "ChampPotentiel") {balise = $ChampPotentiel;}
	else if (nom == "Dimensions") {balise = $Dimensions;}
	else if (nom == "Lambda") {balise = $Lambda;}
	else if (nom == "Epsilon") {balise = $Epsilon;}
	else if (nom == "Systeme") {balise = $Systeme;}
	else if (nom == "Vinf") {balise = $Vinf;}
	else if (nom == "Altitude") {balise = $Altitude;}
	else if (nom == "SousDivisions") {balise = $SousDivisions;}
	else if (nom == "Centre") {balise = $Centre;}
	else if (nom == "Etalement") {balise = $Etalement;}
	else {balise = $invalid;}
	return balise;
}

void Parseur::testBalise(string nom, ifstream& fichier, bool fermee) {
	Balise test(convertBalise(nom,fichier));
	if (test == $invalid) {
		string ouvrante = "<";
		if (fermee) {ouvrante += '/';}
		string message = ouvrante+nom+"> inconnue au bataillon";
		erreur(message,fichier);
	}
}

bool Parseur::testPrecedente(string precedente) {
	string courante(acces.top());
	acces.pop();
	if (acces.top() == precedente) {
		acces.push(courante);
		return true;
	}
	else {
		acces.push(courante);
		return false;
	}
}

int main() {
	Parseur parseur(true);
	parseur.extraire("fichier");
	
	return 0;
}
	
