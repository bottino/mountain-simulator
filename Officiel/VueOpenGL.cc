#include "VueOpenGL.h"
#include "Application.h"

using namespace std; 

Camera camera;
int lx; int ly;

VueOpenGL::VueOpenGL(wxWindow* parent, wxSize const& taille, wxPoint const& position)
:wxGLCanvas(parent, wxID_ANY, position, taille, wxSUNKEN_BORDER)
{
    Connect(wxEVT_PAINT, wxPaintEventHandler(VueOpenGL::dessine));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(VueOpenGL::appuiTouche));
    /*Connect(wxEVT_MOTION, wxMouseEventHandler(VueOpenGL::mouvementSouris));
	Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_LEFT_UP, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(VueOpenGL::clicSouris));
	Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(VueOpenGL::moletteSouris)); */
}
void VueOpenGL::clicSouris(wxMouseEvent& event)
{
    event.GetPosition(&lxSouris,&lySouris);
}
 
void VueOpenGL::moletteSouris(wxMouseEvent& event)
{
    camera.setRayon(camera.getRayon()-event.GetWheelRotation()/120.0);
    Refresh(false);
}
void VueOpenGL::mouvementSouris(wxMouseEvent& event)
{
    if (event.RightIsDown())
    {
        int x(0), y(0);
        event.GetPosition(&x,&y);
         
        camera.setTheta(camera.getTheta()-(lySouris-y)/2);
        camera.setPhi(camera.getPhi()+(lxSouris-x)/2);
         
        event.GetPosition(&lxSouris,&lySouris);
        Refresh(false);
    }
}   ;
void VueOpenGL::InitOpenGL()
{
//indique que les instructions OpenGL s'adressent au contexte
// OpenGL courant
SetCurrent();
 
// Active la gestion de la profondeur
glEnable(GL_DEPTH_TEST);
 
// Fixe la perspective
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

gluPerspective(65.0, 4./3., 1.0, 1000.0);
 
// fixe le fond d'écran 
glClearColor(0.7, 0.8, 1.0, 1.0);
 
// prépare à travailler sur le modèle  
// (données de l'application)
glMatrixMode(GL_MODELVIEW);
}

void VueOpenGL::dessine(wxPaintEvent& event)
{
    // indique que le code est relatif au contexte OPenGL courant
    SetCurrent();
     //initialise les données liées à la gestion de la profondeur
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     
    // initialise GL_MODELVIEW
    // place le repère en (0,0,0)
    glLoadIdentity();
 
   // place la caméra (fixe le point de vue)
	camera.setVue();
		// dessin
	glPushMatrix();
	glTranslated(-15.,-15.,0.);
	wxGetApp().dessine();
	glPopMatrix();
	
    // Finalement, envoi du dessin à l écran
    glFlush();
    SwapBuffers();
}




void VueOpenGL::appuiTouche(wxKeyEvent& event)
{
	switch(event.GetKeyCode())
	{
		case WXK_LEFT:
			camera.setPhi(camera.getPhi() - 0.1);
			break;
			case WXK_RIGHT:
			camera.setPhi(camera.getPhi() + 0.1);
			break;
			case WXK_UP:
				camera.setTheta(camera.getTheta() - 0.1);
			break;
			case WXK_DOWN:
				camera.setTheta(camera.getTheta() + 0.1);
			break;
			case 'W': //Attention
				camera.setRayon(camera.getRayon() - 0.5);
			break;
			case 'S':
				camera.setRayon(camera.getRayon() + 0.5);
			break;
	}
	Refresh(false);
}
