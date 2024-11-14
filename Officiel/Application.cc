#include "Application.h"
#include "Systeme.h"
#include <iostream>
#include "Montagne3D.h"	


void Application::setSysteme(Systeme* s) {systeme=s;}
	
bool Application::OnInit()
{	
	(*systeme).demarre();
    //On alloue les fenêtre
    fenetreGL=new FenetreGL(wxT("Fenetre OpenGL"),wxSize(1200*1.5, 800*1.5));
    
        //Définie comme fenêtre principale
    SetTopWindow(fenetreGL);
     
    //La fonction doit retourner true si elle s'est bien initialisée
    //Si le pointeur est nul, la fenêtre n'a pas pu s'initialiser!
	
	timer=new wxTimer(this);
	timer->Start(500);
	Connect(wxID_ANY, wxEVT_TIMER, wxTimerEventHandler(Application::evolue));
	b=true;
return (fenetreGL!=0);

}
void Application::dessine() {
glPushMatrix();
double l((*systeme).getChampot().getLambda());
glScaled(l,l,l);
(*systeme).dessine();
glPopMatrix();
}

void Application::OnOff() {
	if (b) {timer->Stop(); b = false;} else {timer->Start(150); b=true;}
}
void Application::rafraichir() {fenetreGL->rafraichir();}
GLuint* Application::getTexture(string fichier, bool mipmap)
{
   return texturemanager.getTexture(fichier, mipmap) ;
}
void Application::evolue(wxTimerEvent& event)
{ 
    (*systeme).evolue();
    rafraichir();
}


void Application::mixImages(string nom1, string nom2, string nom3, vector<vector<vector<double> > > carte) {
	texturemanager.mixImages(nom1,nom2,nom3,carte);
}


IMPLEMENT_APP_NO_MAIN(Application);
