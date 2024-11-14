/*
 * EPFL
 * CAESV3
 * Guide wxWidgets et OpenGL
 */

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "wxIncludes"
#include <string>
#include <vector>
#include <map>

using namespace std;
 
class TextureManager
{
	public:
		TextureManager();
		~TextureManager();
		void chargerTexture(std::string fichier, bool mipmap=false);
		GLuint* getTexture(std::string fichier, bool mipmap=false);
		void mixImages(string,string,string,vector<vector<vector<double> > >);
		vector<vector<double> > setMult(vector<vector<vector<double> > > carte);
		void filtreFlou(vector<vector<vector<double> > >&);
	private:
		std::map<std::string, GLuint> textures;
};

#endif
