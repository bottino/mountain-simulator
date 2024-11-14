#include "Control.h"
#include "Conversions.h"
#include "Application.h"
#include "Systeme.h"
#include "Montagne3D.h"
#include "ChampPotentiel.h"
#include "Ciel.h"
#include "Dessinable.h"
#include "wxIncludes"
#include "MontagneHMB.h"
#include "Ciel3D.h"


Control::Control(wxString titre, wxSize taille)
: wxFrame(0, wxID_ANY, titre, wxDefaultPosition, taille, wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{wxString choix[2]={wxT("Montagne Height_Map_Based."), wxT("Montagne gaussienne")};
wxString reponse= wxGetSingleChoice(wxT("Choisissez votre montagne"), wxT("Montagne"), 2,choix);
tab = new vector<ChaineMontagne*>(0);
if (reponse == choix[0]) { hmb = true;
	texteh = textex=new wxStaticText(this, wxID_ANY, wxT("Hauteur max"), wxPoint(0,5));
	tailleh= new wxSlider(this, wxID_ANY, 15, 1, 100, wxPoint(0,20), wxSize(200,25));
	labelh= new wxStaticText(this, wxID_ANY, wxT("15") , wxPoint(230,26));
	texteepsilon = new wxStaticText(this, wxID_ANY, wxT("Epsilon (ChampPotentiel)"), wxPoint(0,43));
	tailleepsilon= new wxSlider(this, wxID_ANY, 10, 1, 100, wxPoint(0,60), wxSize(200,25));
	labelepsilon= new wxStaticText(this, wxID_ANY, wxT("0.1") , wxPoint(230,63));
	textelambda = new wxStaticText(this, wxID_ANY, wxT("Lambda (ChampPotentiel)"), wxPoint(0,85));
	taillelambda= new wxSlider(this, wxID_ANY, 20, 1, 100, wxPoint(0,100), wxSize(200,25));
	labellambda= new wxStaticText(this, wxID_ANY, wxT("20") , wxPoint(230,105));
	textevent = textex=new wxStaticText(this, wxID_ANY, wxT("Vent dans la plaine"), wxPoint(0,129));
	taillevent= new wxSlider(this, wxID_ANY, 20, 1, 100, wxPoint(0,143), wxSize(200,25));
	labelvent= new wxStaticText(this, wxID_ANY, wxT("20") , wxPoint(230,147));
	diffusion = new wxCheckBox(this, wxID_ANY, wxT("Diffusion de l'humidité"), wxPoint(0,175), wxSize(200,25));
	wxWindowID ID_envoi(NewControlId());
	envoi = new wxButton(this, ID_envoi, wxT("Créer"), wxPoint(230,330) , wxSize(50,30));
	
	Connect(ID_envoi, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Control::creation));
	}
else if (reponse==choix[1] ){ hmb = false;
	textex=new wxStaticText(this, wxID_ANY, wxT("Taille x"), wxPoint(0,2));
	taillex = new wxSlider(this, wxID_ANY, 30, 1, 100, wxPoint(0,15), wxSize(200,25));
	labelx=new wxStaticText(this, wxID_ANY, wxT("30") , wxPoint(230,20));
	textey=new wxStaticText(this, wxID_ANY, wxT("Taille y"), wxPoint(0,40));
	tailley = new wxSlider(this, wxID_ANY, 30, 1, 100, wxPoint(0,50), wxSize(200,25));
	labely=new wxStaticText(this, wxID_ANY, wxT("30") , wxPoint(230,57));
	textez=new wxStaticText(this, wxID_ANY, wxT("Taille z"), wxPoint(0,75));
	taillez = new wxSlider(this, wxID_ANY, 30, 1, 100, wxPoint(0,85), wxSize(200,25));
	labelz= new wxStaticText(this, wxID_ANY, wxT("30") , wxPoint(230,94));
	/*texteh = textex=new wxStaticText(this, wxID_ANY, wxT("Hauteur max"), wxPoint(0,110));
	tailleh= new wxSlider(this, wxID_ANY, 15, 1, 100, wxPoint(0,125), wxSize(200,25));
	labelh= new wxStaticText(this, wxID_ANY, wxT("15") , wxPoint(230,131));
	texteepsilon = textex=new wxStaticText(this, wxID_ANY, wxT("Epsilon (ChampPotentiel)"), wxPoint(0,148));
	tailleepsilon= new wxSlider(this, wxID_ANY, 10, 1, 100, wxPoint(0,165), wxSize(200,25));
	labelepsilon= new wxStaticText(this, wxID_ANY, wxT("0.1") , wxPoint(230,168));*/
	textelambda = textex=new wxStaticText(this, wxID_ANY, wxT("Lambda (ChampPotentiel)"), wxPoint(0,110));
	taillelambda= new wxSlider(this, wxID_ANY, 20, 1, 100, wxPoint(0,125), wxSize(200,25));
	labellambda= new wxStaticText(this, wxID_ANY, wxT("20") , wxPoint(230,131));
	textevent = textex=new wxStaticText(this, wxID_ANY, wxT("Vent dans la plaine"), wxPoint(0,148));
	taillevent= new wxSlider(this, wxID_ANY, 20, 1, 100, wxPoint(0,168), wxSize(200,25));
	labelvent= new wxStaticText(this, wxID_ANY, wxT("20") , wxPoint(230,168));
	
	mode_texte = new wxCheckBox(this, wxID_ANY, wxT("Mode texte"), wxPoint(0, 260), wxSize(200,25));
	diffusion = new wxCheckBox(this, wxID_ANY, wxT("Diffusion de l'humidité"), wxPoint(0,280), wxSize(200,25));
	
	textexm=new wxStaticText(this, wxID_ANY, wxT("Etalemement en x"), wxPoint(0,315));
	taillexm = new wxSlider(this, wxID_ANY, 15, 1, 100, wxPoint(0,325), wxSize(200,25));
	labelxm=new wxStaticText(this, wxID_ANY, wxT("15") , wxPoint(230,327));
	texteym=new wxStaticText(this, wxID_ANY, wxT("Etalement en y"), wxPoint(0,350));
	tailleym = new wxSlider(this, wxID_ANY, 15, 1, 100, wxPoint(0,360), wxSize(200,25));
	labelym=new wxStaticText(this, wxID_ANY, wxT("15") , wxPoint(230,365));
	textezm=new wxStaticText(this, wxID_ANY, wxT("Hauteur"), wxPoint(0,385));
	taillezm = new wxSlider(this, wxID_ANY, 15, 1, 100, wxPoint(0,395), wxSize(200,25));
	labelzm=new wxStaticText(this, wxID_ANY, wxT("15") , wxPoint(230,400));
	
	textesx=new wxStaticText(this, wxID_ANY, wxT("Sx"), wxPoint(0,420));
	taillesx = new wxSlider(this, wxID_ANY, 5, 1, 100, wxPoint(0,430), wxSize(200,25));
	labelsx=new wxStaticText(this, wxID_ANY, wxT("5") , wxPoint(230,432));
	textesy=new wxStaticText(this, wxID_ANY, wxT("Sy"), wxPoint(0,455));
	taillesy = new wxSlider(this, wxID_ANY, 5, 1, 100, wxPoint(0,470), wxSize(200,25));
	labelsy=new wxStaticText(this, wxID_ANY, wxT("5") , wxPoint(230,470));
	wxWindowID ID_envoi(NewControlId());
	wxWindowID ID_montagne(NewControlId());
	envoi = new wxButton(this, ID_envoi, wxT("Créer"), wxPoint(230,540), wxSize(50,30));
	montagne = new wxButton(this, ID_montagne, wxT("Ajouter une montagne"), wxPoint(100, 540), wxSize(60, 100));
	
	Connect(ID_montagne, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Control::ajoute_montagne));
	Connect(ID_envoi, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(Control::creation));
}
    Center();
    //Et on l'affiche
    Show();
    
    Connect(wxID_ANY, wxEVT_COMMAND_SLIDER_UPDATED, wxScrollEventHandler(Control::sliderModifie));
    
};

void Control::creation(wxCommandEvent& event) {
	if (hmb) {
	MontagneHMB* m1 = new MontagneHMB(30.,30.,tailleh->GetValue(),3.);
	ChampPotentiel* champot = new ChampPotentiel(30.,30.,30.,(taillelambda->GetValue())/30.,tailleepsilon->GetValue()/100., *m1, taillevent->GetValue()); 
	Ciel3D* c = new Ciel3D(*champot);
	Systeme* sys = new Systeme(*champot, *c, diffusion->GetValue());
	wxGetApp().setSysteme(sys);
	wxGetApp().OnInit();
}
 else { if ((*tab).size() != 0) {
	 if (mode_texte->GetValue()) {
	//Montagne* m1 = new Montagne3D(taillex->GetValue(),tailley->GetValue(),taillexm->GetValue(),tailleym->GetValue(),taillezm->GetValue(),taillesx->GetValue(),taillesy->GetValue());
	ChaineMontagne* v1 = new ChaineMontagne(*tab, taillex->GetValue(),tailley->GetValue());
	ChampPotentiel* champot = new ChampPotentiel(taillex->GetValue(),tailley->GetValue(),taillez->GetValue(),(taillelambda->GetValue())/(taillez->GetValue()-1.),0.1, *v1, taillevent->GetValue()); 
	Ciel* c = new Ciel3D(*champot);
	Systeme* sys = new Systeme(*champot, *c, diffusion->GetValue(), mode_texte->GetValue());
	wxGetApp().setSysteme(sys);
	wxGetApp().OnInit();	 
	 } else {	 ChaineMontagne3D* v1 = new ChaineMontagne3D(*tab,taillex->GetValue(),tailley->GetValue());
	//Montagne3D* m1 = new Montagne3D(taillex->GetValue(),tailley->GetValue(),taillexm->GetValue(),tailleym->GetValue(),taillezm->GetValue(),taillesx->GetValue(),taillesy->GetValue());
	ChampPotentiel* champot = new ChampPotentiel(taillex->GetValue(),tailley->GetValue(),taillez->GetValue(),(taillelambda->GetValue())/(taillez->GetValue()-1.),0.1, *v1, taillevent->GetValue()); 
	Ciel3D* c = new Ciel3D(*champot);
	Systeme* sys = new Systeme(*champot, *c, diffusion->GetValue(), mode_texte->GetValue());
	wxGetApp().setSysteme(sys);
	wxGetApp().OnInit();
	}
	} else { wxMessageBox(wxT("Ajoutez au moins une montagne!"));}
	
}	
}


void Control::sliderModifie(wxScrollEvent& event) {
	if (hmb) {
	labelh->SetLabel(int2wxString(tailleh->GetValue()));
	labelepsilon->SetLabel(double2wxString(tailleepsilon->GetValue()/100.));
	labellambda->SetLabel(int2wxString(taillelambda->GetValue()));
	labelvent->SetLabel(int2wxString(taillevent->GetValue()));
}
	else {
	labelsx->SetLabel(int2wxString(taillesx->GetValue()));
	labelsy->SetLabel(int2wxString(taillesy->GetValue()));
	labelx->SetLabel(int2wxString(taillex->GetValue()));
	labely->SetLabel(int2wxString(tailley->GetValue()));
	labelz->SetLabel(int2wxString(taillez->GetValue()));
	labelxm->SetLabel(int2wxString(taillexm->GetValue()));
	labelym->SetLabel(int2wxString(tailleym->GetValue()));
	labelzm->SetLabel(int2wxString(taillezm->GetValue()));
	labellambda->SetLabel(int2wxString(taillelambda->GetValue()));
	labelvent->SetLabel(int2wxString(taillevent->GetValue()));
		
	}
}

void Control::ajoute_montagne(wxCommandEvent& event) {
	if (hmb) {
	(*tab).push_back(new MontagneHMB(30.,30.,tailleh->GetValue(),3.0));
}
 else {
	 if (mode_texte->GetValue()) { 
	(*tab).push_back(new Montagne(taillex->GetValue(), tailley->GetValue(),taillexm->GetValue(),tailleym->GetValue(),taillezm->GetValue(),taillesx->GetValue(),taillesy->GetValue()));
	 } else {	 
	(*tab).push_back(new Montagne3D(taillex->GetValue(), tailley->GetValue(),taillexm->GetValue(),tailleym->GetValue(),taillezm->GetValue(),taillesx->GetValue(),taillesy->GetValue()));
	}
}	
	
}
	
