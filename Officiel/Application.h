#include "wxIncludes"
#include "FenetreGL.h"
#include "TextureManager.h"
#include "Systeme.h"
#include "Control.h" 
 
using namespace std; 
  
class Application : public wxApp //Héritage
{
	public:
	void dessine();
	void setSysteme(Systeme*);
	GLuint* getTexture(string fichier, bool mipmap=true);
	bool OnInit();
	void mixImages(string,string,string,vector<vector<vector<double> > >);
	void OnOff();
	private:
		wxTimer* timer;
		void evolue(wxTimerEvent& event);
		FenetreGL* fenetreGL;
		bool b;
		void rafraichir();
		Systeme* systeme;
		TextureManager texturemanager;
};

DECLARE_APP(Application);
