#ifndef CONTROL_H
#define CONTROL_H

#include "wxIncludes"
#include "FenetreGL.h"
#include <vector>
#include "ChaineMontagne.h"
#include "ChaineMontagne3D.h"

class Control : public wxFrame //Héritage
{
	public:	
	Control(wxString titre, wxSize taille);
	
	private:
	bool hmb;
	vector<ChaineMontagne*> * tab;
	void sliderModifie(wxScrollEvent& event);
	void creation(wxCommandEvent& event);
	void ajoute_montagne(wxCommandEvent& event);
	wxStaticText* textex;
	wxStaticText* textey;
	wxStaticText* textez;
	wxStaticText* textesx;
	wxStaticText* textesy;
	wxStaticText* textexm;
	wxStaticText* texteym;
	wxStaticText* textezm;
	wxStaticText* texteh;
	wxStaticText* texteepsilon;
	wxStaticText* textelambda;
	wxStaticText* textevent;
	wxStaticText* labelx;
	wxStaticText* labely;
	wxStaticText* labelz;
	wxStaticText* labelsx;
	wxStaticText* labelsy;
	wxStaticText* labelxm;
	wxStaticText* labelym;
	wxStaticText* labelzm;
	wxStaticText* labelh;
	wxStaticText* labelepsilon;
	wxStaticText* labellambda;
	wxStaticText* labelvent;
	wxSlider* taillex;
	wxSlider* tailley;
	wxSlider* taillez;
	wxSlider* taillesx;
	wxSlider* taillesy;
	wxSlider* taillexm;
	wxSlider* tailleym;
	wxSlider* taillezm;
	wxSlider* tailleh;
	wxSlider* tailleepsilon;
	wxSlider* taillelambda;
	wxSlider* taillevent;
	wxCheckBox* mode_texte;
	wxCheckBox* diffusion;
	wxButton* montagne;
	wxButton* envoi;
	
};


#endif
