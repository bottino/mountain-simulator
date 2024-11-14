#include "Application.h"
#include "ChampPotentiel.h"
#include "Ciel.h"
#include "Ciel3D.h"
#include "Control.h"
#include "Dessinable.h"
#include "Montagne3D.h"
#include "MontagneHMB.h"
#include "Systeme.h"
#include "wxIncludes"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) { // Déclaration des instances du projet
  /*Montagne3D m1(15.,15.,15.,5.,5.);
  MontagneHMB m1(30.,30.,15.,3.);
  ChampPotentiel champot(30.,30.,30.,(20./29.),0.1, m1, 20.);
  Ciel3D c(champot);
  Systeme sys(champot, c);*/

  Application *app(new Application()); // Création d'une instance de la classe
                                       // Application héritant de wxApp
  wxApp::SetInstance(app);
  wxEntryStart(argc, argv); // Initialisation de wxWidgets
  Control *control(new Control(wxT("Menu"), wxSize(640 * 0.5, 480 * 1.5)));
  //(*app).setSysteme(&sys);
  // ((wxTheApp->OnInit(); //Appel de la fonction d'initialisation
  // personnalisée.
  // init(app);

  // Appel des fonctions personnalisées
  wxTheApp->OnRun();
  wxTheApp->OnExit();
  wxEntryCleanup(); // Libère les ressources allouées par wxEntryStart

  return 0;
}
