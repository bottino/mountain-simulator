#ifndef FENETREGL_H
#define FENETREGL_H
 
#include "wxIncludes"
#include "VueOpenGL.h"
 
class FenetreGL : public wxFrame //Héritage
{
    public:
        FenetreGL(wxString titre, wxSize taille);
		void rafraichir();

    private:
	VueOpenGL* vueopengl;
};
#endif
