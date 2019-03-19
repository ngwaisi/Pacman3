/*
Test de A * sur une carte routi鑢e

*/
#include <iostream>
//#include <fstream>

#include "InfosGrapheDessin.h"
#include "InfoAStar.h"
#include "InfoSommet.h"
#include "Sommet.h"
#include"InfoArete.h"
#include "Arete.h"

#include "Graphe.h"
#include "AStarT.h"
#include "Outils.h"
#include "OutilsCarte.h"
#include "FenetreGrapheSFML.h"
#include"FenetreGrapheSFMLAStar.h"
#include "SFML/Window/Event.hpp"
#include <stdlib.h>
#include <SFML/Graphics/Font.hpp>

#include <string>
#include "Vecteur2D.h"
#include "PElement.h"

using namespace std;
using namespace sf;

int main()
{
	cout << "essai de AStarT" << endl;

	Sommet<InfoSommet> * sA, *sB, *sC, *sD, *sE, *sF, *sG;

	Arete<InfoArete, InfoSommet> * aAB, *aAC, *aAD, *aBC, *aCD, *aCE, *aCF, *aDE, *aDF, *aEF;

	//-------------------- cr閍tion d'un graphe repr閟entant une carte routi鑢e -----------------------------

	Graphe<InfoArete, InfoSommet> graphe;

	//------------------  insertion des sommets -------------------------------

	unsigned int vert = 0x00FF00FF; // vert opaque : couleur des sommets

	sA = graphe.creeSommet(InfoSommet(VSommet("A", Vecteur2D(6, 8), vert), InfoAStar())); 		// Sommet<T> * creeSommet(const T & info);
	sB = graphe.creeSommet(InfoSommet(VSommet("B", Vecteur2D(7, 3), vert), InfoAStar()));
	sC = graphe.creeSommet(InfoSommet(VSommet("C", Vecteur2D(5, 1), vert), InfoAStar()));
	sD = graphe.creeSommet(InfoSommet(VSommet("D", Vecteur2D(2, 4), vert), InfoAStar()));
	sE = graphe.creeSommet(InfoSommet(VSommet("E", Vecteur2D(1, 1), vert), InfoAStar()));
	sF = graphe.creeSommet(InfoSommet(VSommet("F", Vecteur2D(3, 2), vert), InfoAStar()));
	sG = graphe.creeSommet(InfoSommet(VSommet("G", Vecteur2D(3, 8), vert), InfoAStar()));

	//------------------------ insertion des ar阾es ------------------------------------

	//aAB = graphe.creeArete(sA,sB,double(OutilsCarte::distance(sA,sB)));
	//aAC = graphe.creeArete(sA,sC,double(OutilsCarte::distance(sA,sC)));
	//aAD = graphe.creeArete(sA,sD,double(OutilsCarte::distance(sA,sD)));
	//aBC = graphe.creeArete(sB,sC,double(OutilsCarte::distance(sB,sC)));
	//aCD = graphe.creeArete(sC,sD,double(OutilsCarte::distance(sC,sD)));
	//aCE = graphe.creeArete(sC,sE,double(OutilsCarte::distance(sC,sE)));
	//aCF = graphe.creeArete(sC,sF,double(OutilsCarte::distance(sC,sF)));
	//aDE = graphe.creeArete(sD,sE,double(OutilsCarte::distance(sD,sE)));
	//aDF = graphe.creeArete(sD,sF,double(OutilsCarte::distance(sD,sF)));
	//aEF = graphe.creeArete(sE,sF,double(OutilsCarte::distance(sE,sF)));

	aAB = OutilsCarte::creeArete(sA, sB, graphe);
	aAC = OutilsCarte::creeArete(sA, sC, graphe);
	aAD = OutilsCarte::creeArete(sA, sD, graphe);
	aBC = OutilsCarte::creeArete(sB, sC, graphe);
	aCD = OutilsCarte::creeArete(sC, sD, graphe);
	aCE = OutilsCarte::creeArete(sC, sE, graphe);
	aCF = OutilsCarte::creeArete(sC, sF, graphe);
	aDE = OutilsCarte::creeArete(sD, sE, graphe);
	aDF = OutilsCarte::creeArete(sD, sF, graphe);
	aEF = OutilsCarte::creeArete(sE, sF, graphe);

	cout << "la carte routi鑢e cr殚e est :" << endl << graphe << endl;

	char ch; cin >> ch;
	cout << "les ar阾es adjacentes de de C sont : " << endl << graphe.aretesAdjacentes(sC);
	cout << "les ar阾es adjacentes de de F sont : " << endl << graphe.aretesAdjacentes(sF);
	cout << "les ar阾es adjacentes de de G sont : " << endl << graphe.aretesAdjacentes(sG);
	cin >> ch;
	cout << endl;

	cout << "les voisins de de C sont : " << endl << graphe.voisins(sC);
	cout << "les voisins de de F sont : " << endl << graphe.voisins(sF);
	cout << "les voisins de de G sont : " << endl << graphe.voisins(sG);
	cin >> ch;
	cout << endl;
	cout << "les adjacences de de C sont : " << endl << graphe.adjacences(sC);

	cin >> ch;

	Sommet<InfoSommet> * depart = sA;
	OutilsCarte::cible = sG;
	Sommet<InfoSommet> * resultat;

	resultat = AStarT< Graphe<InfoArete, InfoSommet>, Sommet<InfoSommet> >::aStar(graphe, depart, OutilsCarte::hh);

	cout << "succes = " << (resultat != NULL) << endl;

	cout << "la carte routi鑢e apr鑣 recherche du chemin de sA ?sG par A* est :" << endl << graphe << endl;

	cin >> ch;

	OutilsCarte::cible = sE;

	resultat = AStarT< Graphe<InfoArete, InfoSommet>, Sommet<InfoSommet> >::aStar(graphe, depart, OutilsCarte::hh);

	cout << "succes = " << (resultat != NULL) << endl;

	cout << "la carte routi鑢e apr鑣 recherche du chemin de sA ?sE par A* est :" << endl << graphe << endl;
	cin >> ch;

	PElement<Sommet<InfoSommet>> * c;
	chemin(sE, c);					// construit le chemin c qui part de SA vers SE ?partir de la liste "p鑢e" produite par A*

	cout << "le chemin trouv?de de sA ?sE par A* est :" << endl << c << endl;
	cin >> ch;

	string titre("Recherche d'un chemin dans un graphe ?l'aide de l'algo A*");

	//Vecteur2D  coinBG(0,hauteur), coinHD(largeur,0);

	unsigned int fondCarte = 0xEFEFEFFF;	// sorte de gris clair ~= 閠ain pur

	Vecteur2D  coinBG(-1, -1);
	Vecteur2D  coinHD(10, 10);

	int largeur = 800, hauteur = 400;
	Font font1, font2;
	string cheminFontes = "..\\..\\graphes\\mespolices\\";
	string nomFichierFonte1 = cheminFontes + "abaddon.ttf";
	string nomFichierFonte2 = cheminFontes + "ActionManBoldItalic.ttf";
	bool ok = font1.loadFromFile(nomFichierFonte1);
	ok = font2.loadFromFile(nomFichierFonte2);
	FenetreGrapheSFMLAvecAxesRepereMonde fenetreGraphe(titre, fondCarte, coinBG, coinHD, largeur, hauteur, font2, font2);

	ok = graphe.dessineToutesAretes(fenetreGraphe);

	unsigned int couleurChemin = 0xFF0000FF;	// rouge opaque

	ok = dessine(c, fenetreGraphe, couleurChemin);	// dessine le chemin trouv?par l'algo A*

	ok = graphe.dessineTousSommets(fenetreGraphe);

	ok = graphe.dessine(fenetreGraphe);

	cout << "graphe dessin?? " << (ok ? "succ鑣" : "閏hec") << endl;

	fenetreGraphe.fenetre.display();
	//cout << "apr鑣 display" << endl;

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "S");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	//boucle infinie de contr鬺e des 関鑞ements de la fen阾re
	while (fenetreGraphe.fenetre.isOpen())
	{
		Event event;
		while (fenetreGraphe.fenetre.pollEvent(event))
		{
			if (event.type == Event::Closed) /*(event.type == Event::EventType::Closed)*/
				fenetreGraphe.fenetre.close();
		}
	}

	return 0;
}
