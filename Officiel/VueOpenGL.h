#ifndef VUEOPENGL_H
#define VUEOPENGL_H
 
#include "wxIncludes" 
#include "Camera.h"
 
class VueOpenGL: public wxGLCanvas {
public:
    VueOpenGL(wxWindow* parent, wxSize const& taille=wxDefaultSize, wxPoint const& position=wxDefaultPosition);
    void InitOpenGL();
private:
    void dessine(wxPaintEvent& event);
    void appuiTouche(wxKeyEvent& event);
    void clicSouris(wxMouseEvent& event);
    void moletteSouris(wxMouseEvent& event);
    void mouvementSouris(wxMouseEvent& event);
    
    int lxSouris;
    int lySouris;

};

 

#endif
