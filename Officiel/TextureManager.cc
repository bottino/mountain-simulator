
#include "TextureManager.h"
#include <dirent.h>
#include <iterator>
#include <string>

using namespace std;

//Normalement, il marche sans que tu aies besoin de toucher tes autres fichiers

TextureManager::TextureManager()
{
} 
TextureManager::~TextureManager()
{
	//On libère les textures
	for (std::map<std::string,GLuint>::iterator it=textures.begin(); it != textures.end(); ++it) glDeleteTextures(1, &it->second);
}

void TextureManager::chargerTexture(std::string fichier, bool mipmap) {
	
	size_t png = fichier.rfind(".png");
	if (png!=string::npos) {									//Teste s'il s'agit d'un .png
		wxImageHandler* pngLoader = new wxPNGHandler();
		wxImage::AddHandler(pngLoader);
	
		glGenTextures(1, &textures[fichier]);					//Crée un tableau de 1 texture (on pourra peut-être modifier, mais pas indispensable)
		glBindTexture(GL_TEXTURE_2D, textures[fichier]);
	
		std::string imagepath=fichier;
	
		wxImage* img=new wxImage(wxString::From8BitData(imagepath.c_str()), wxBITMAP_TYPE_PNG);		//Teste la présence d'un canal alpha
		if (img->HasAlpha()) {cout <<fichier<< "_Alpha: OK"<<endl;}							//OK s'il y en a un
		else {
			cout <<fichier<< "_Alpha: PAS OK"<<endl;
			img->InitAlpha();
			if (img->HasAlpha()) {cout << "Maintenant c'est bon."<<endl;} else {cout << "Quand ça veut pas..."<<endl;}	//Sinon, on tente d'en créer un. Pour moi, ça a tjrs marché avec les png
		}
	
		GLubyte* imagedata=img->GetData();								//Met les données RGB de l'image dans un tableau
		GLubyte* imagealpha=img->GetAlpha();							//Met les données Alpha de l'image dans un autre tableau
		GLubyte data[img->GetWidth()*img->GetHeight()*4];
		for (size_t x(0); x < img->GetWidth()*img->GetHeight(); ++x) {	//Mixe les deux pour faire un tableau RGBARGBARG...
			data[4*x]=imagedata[3*x];
			data[4*x+1]=imagedata[3*x+1];
			data[4*x+2]=imagedata[3*x+2];
			data[4*x+3]=imagealpha[x];
		}
	
		if (mipmap)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, img->GetWidth(), img->GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, data);	//Crée la texture

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, 4, img->GetWidth(), img->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data);	//Crée la texture
	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		free(img);
		free(imagedata);
		free(imagealpha);
	}
	
	else {																//Prend une texture jpeg (sans test), TextureManager habituel
		wxImageHandler* jpegLoader = new wxJPEGHandler();
		wxImage::AddHandler(jpegLoader);
		
		glGenTextures(1, &textures[fichier]);
		glBindTexture(GL_TEXTURE_2D, textures[fichier]);
	
		std::string imagepath=fichier;
	
		wxImage* img=new wxImage(wxString::From8BitData(imagepath.c_str()), wxBITMAP_TYPE_JPEG);
		
		GLubyte* imagedata=img->GetData();
		
		if (mipmap) {
			gluBuild2DMipmaps(GL_TEXTURE_2D, 3, img->GetWidth(), img->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, imagedata);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else {
			glTexImage2D(GL_TEXTURE_2D, 0, 3, img->GetWidth(), img->GetHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, imagedata);
	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		free(img);
		free(imagedata);
	}
}

GLuint* TextureManager::getTexture(std::string fichier, bool mipmap)
{
	if (textures.find(fichier)==textures.end()) chargerTexture(fichier, mipmap);
	return &textures[fichier];
}

void TextureManager::mixImages(string nom1, string nom2, string nom3, vector<vector<vector<double> > > carte) {
	
	wxImageHandler* jpegLoader = new wxJPEGHandler();
	wxImage::AddHandler(jpegLoader);
	
	string imagepath1 = nom1;
	string imagepath2 = nom2;
	string imagepath3 = nom3;
	
	wxImage* image1 = new wxImage(wxString::From8BitData(imagepath1.c_str()), wxBITMAP_TYPE_JPEG);
	wxImage* image2 = new wxImage(wxString::From8BitData(imagepath2.c_str()), wxBITMAP_TYPE_JPEG);
	wxImage* image3 = new wxImage(wxString::From8BitData(imagepath3.c_str()), wxBITMAP_TYPE_JPEG);
	wxImage image(image1->GetWidth(), image1->GetHeight());
	
	GLubyte* data1 = image1->GetData();
	GLubyte* data2 = image2->GetData();
	GLubyte* data3 = image3->GetData();
	GLubyte data[image1->GetWidth()*image1->GetHeight()*3];
	
	vector<vector<double> > mult(image1->GetWidth()*image1->GetHeight(), vector<double>(3,0.));
	if (carte.size()*carte[0].size()*100 == image.GetWidth()*image.GetHeight()) {
		mult = setMult(carte);
	}
	
	/*for (size_t i(0); i<mult.size(); ++i) {
		if (i%2==0) {mult[i]=0.;}
		else {mult[i]=1.;}
	}*/
	
	if (image1->GetWidth() == image2->GetWidth() and image1->GetHeight() == image2->GetHeight()) {
		for (size_t x(0); x < image1->GetWidth()*image1->GetHeight(); ++x) {
			data[3*x  ] = mult[x][0]*data1[3*x  ] + mult[x][1]*data2[3*x  ] + mult[x][2]*data3[3*x  ];
			data[3*x+1] = mult[x][0]*data1[3*x+1] + mult[x][1]*data2[3*x+1] + mult[x][2]*data3[3*x+1];
			data[3*x+2] = mult[x][0]*data1[3*x+2] + mult[x][1]*data2[3*x+2] + mult[x][2]*data3[3*x+2];
		}
	}
	else {cout << "TextureManager::mixImages : erreur : images de dimensions differentes" << endl;}
	
	int dimx(image.GetWidth());
	int dimy(image.GetHeight());
	
	for (int x(0); x<dimx; ++x) {
		for (int y(0); y<dimy; ++y) {
			image.SetRGB(x,y,data[3*(dimy*x+y)],data[3*(dimy*x+y)+1],data[3*(dimy*x+y)+2]);
		}
	}
	
	//image.SetData(data);
	image.Rescale(1024,1024,wxIMAGE_QUALITY_HIGH);
	string nomSortie("textures/textureMixee.jpg");
	image.SaveFile(wxString::From8BitData(nomSortie.c_str()), wxBITMAP_TYPE_JPEG);
	
	
}

vector<vector<double> > TextureManager::setMult(vector<vector<vector<double> > > carte) {
	
	int dimx(carte.size());
	int dimy(carte[0].size());
	
	filtreFlou(carte);
	filtreFlou(carte);
	filtreFlou(carte);
		
	vector<vector<double> > mult(100*dimx*dimy, vector<double>(3, 0.));
	vector<vector<vector<double> > > inter(10*dimx, vector<vector<double> >(10*dimy, vector<double>(3, 0.)));
	for (size_t x(0); x<dimx; ++x) {
		for (size_t y(0); y<dimy; ++y) {
			for (size_t k1(0); k1<10; ++k1) {
				for (size_t k2(0); k2<10; ++k2) {
											
					inter[10*x+k1][10*y+k2] = carte[x][y];
				}
			}
		}
	}
	
	filtreFlou(inter);
	filtreFlou(inter);
	filtreFlou(inter);
	filtreFlou(inter);
	filtreFlou(inter);
	filtreFlou(inter);
	
	for (size_t x(0); x<10*dimx; ++x) {
		for (size_t y(0); y<10*dimy; ++y) {
			mult[10*dimy*x+y] = inter[x][y];
		}
	}
	return mult;
}

void TextureManager::filtreFlou(vector<vector<vector<double> > >& image) {
	
	int dimx(image.size());
	int dimy(image[0].size());
	
	vector<vector<vector<double> > > imageFiltree;
    imageFiltree.resize(dimx);
	for (double x(0); x < dimx; ++x) {
        imageFiltree[x].resize(dimy);
        for (double y(0); y < dimy; ++y) {
			imageFiltree[x][y].resize(3);
            vector<double> moyenne(3,0.);
            vector<double> denom(3,0.);
            if (x-1>=0 and y-1>=0 and x-1<dimx and y-1<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x-1][y-1][i];
					++denom[i];
				}
            }
            if (x-1>=0 and y>=0 and x-1<dimx and y<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x-1][y][i];
					++denom[i];
				}
            }
            if (x-1>=0 and y+1>=0 and x-1<dimx and y+1<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x-1][y+1][i];
					++denom[i];
				}
            }
            if (x>=0 and y-1>=0 and x<dimx and y-1<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x][y-1][i];
					++denom[i];
				}
            }
            if (x>=0 and y>=0 and x<dimx and y<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x][y][i];
					++denom[i];
				}
            }
            if (x>=0 and y+1>=0 and x<dimx and y+1<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x][y+1][i];
					++denom[i];
				}
            }
            if (x+1>=0 and y-1>=0 and x+1<dimx and y-1<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x+1][y-1][i];
					++denom[i];
				}
            }
            if (x+1>=0 and y>=0 and x+1<dimx and y<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x+1][y][i];
					++denom[i];
				}
            }
            if (x+1>=0 and y+1>=0 and x+1<dimx and y+1<dimy) {
                for (int i(0); i<3; ++i) {
					moyenne[i] += image[x+1][y+1][i];
					++denom[i];
				}
            }
            for (int i(0); i<3; ++i) {
				moyenne[i] /= denom[i];
				imageFiltree[x][y][i] = moyenne[i];
			}
        }
    }
    image=imageFiltree;
}
    
	






