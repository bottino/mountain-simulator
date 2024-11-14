CXX = g++-4.7
CC  = $(CXX)

CXXFLAGS = -std=c++11 -Wall
CXXFLAGS += `wx-config --cxxflags`
CXXFLAGS += -g -pg
CXXFLAGS += -O2
LDFLAGS  += -L/usr/X11R6/lib/
LDLIBS   = -lglut -lGLU -lGL -lXmu -lXi `wx-config --libs gl,core,base`


all: simulation

simulation.o : simulation.cc
simulation: Application.o VueOpenGL.o Camera.o Systeme.o Potentiel.o Montagne.o ChampPotentiel.o Vecteur2D.o CubeDAir.o Ciel.o Ciel3D.o Montagne3D.o ChaineMontagne.o Dessinable.o FenetreGL.o TextureManager.o Couleur.o Terrain.o Sapin.o Soleil.o MontagneHMB.o Billboard.o Control.o Conversions.o ChaineMontagne3D.o

Control.o: Control.cc
Application.o : Application.cc
VueOpenGL.o : VueOpenGL.cc
Camera.o : Camera.cc
TextureManager.o : TextureManager.cc
FenetreGL.o: FenetreGL.cc FenetreGL.h
Sapin.o: Sapin.cc
Soleil.o: Soleil.cc
MontagneHMB.o: MontagneHMB.cc
Billboard.o: Billboard.cc
Conversions.o : Conversions.cc

Terrain.o : Terrain.cc
Couleur.o : Couleur.cc
TestVecteur2D.o : TestVecteur2D.cc
TestMontagne.o : TestMontagne.cc
TestLaplace.o : TestLaplace.cc
Vecteur2D.o : Vecteur2D.cc
Potentiel.o : Potentiel.cc
Dessinable.o : Dessinable.cc
ChampPotentiel.o : ChampPotentiel.cc
Montagne.o : Montagne.cc
Montagne3D.o : Montagne3D.cc
ChaineMontagne.o : ChaineMontagne.cc
ChaineMontagne3D.o: ChaineMontagne3D.cc
CubeDAir.o : CubeDAir.cc constantes.h
Ciel.o : Ciel.cc
Ciel3D.o : Ciel3D.cc
Systeme.o : Systeme.cc
TestMontagne2.o : TestMontagne2.cc
TestP11.o : TestP11.cc
TestPotentiel.o : TestPotentiel.cc
TestSysteme.o : TestSysteme.cc
TestPotentiel : TestPotentiel.o Potentiel.o ChampPotentiel.o Vecteur2D.o Montagne.o
TestDessine.o : TestDessine.cc
P15.o : P15.cc

TestMontagne : TestMontagne.o Montagne.o
TestMontagne2 : TestMontagne2.o ChaineMontagne.o Montagne.o
TestVecteur2D: TestVecteur2D.o Vecteur2D.o 
TestLaplace: TestLaplace.o Potentiel.o Montagne.o ChampPotentiel.o Vecteur2D.o
TestNuage: TestNuage.o Potentiel.o Montagne.o ChampPotentiel.o Vecteur2D.o CubeDAir.o Ciel.o
TestSysteme: TestSysteme.o Systeme.o Potentiel.o Montagne.o ChampPotentiel.o Vecteur2D.o CubeDAir.o Ciel.o
TestDessine: TestDessine.o Potentiel.o Montagne.o ChampPotentiel.o Vecteur2D.o CubeDAir.o Ciel.o
TestSysteme: TestSysteme.o Systeme.o Potentiel.o Montagne.o ChampPotentiel.o Vecteur2D.o CubeDAir.o Ciel.o
TestP11: TestP11.o Systeme.o Potentiel.o Montagne.o ChampPotentiel.o Vecteur2D.o CubeDAir.o Ciel.o Ciel3D.o Dessinable.o ChaineMontagne.o
P15: P15.o Systeme.o Potentiel.o Montagne.o ChampPotentiel.o Vecteur2D.o CubeDAir.o Ciel.o Ciel3D.o Montagne3D.o ChaineMontagne.o Dessinable.o



make clean:
	-rm -f *.o
