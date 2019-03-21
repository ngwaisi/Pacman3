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
//#include "Graphe"
#include "Graphe.h"
#include "AStarT.h"
#include "Outils.h"
#include "OutilsCarte.h"
#include "FenetreGrapheSFML.h"
#include"FenetreGrapheSFMLAStar.h"
#include "SFML/Window/Event.hpp"
#include <stdlib.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML\Graphics\Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
//#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
//#include <SFML/Graphics/Font.hpp>
#include <string>
#include "Vecteur2D.h"
#include "PElement.h"
#include "InfosGrapheDessin.h"
using namespace std;
using namespace sf;

/*
Test de l'opération dessiner un graphe planaire
L'info associée aux sommets est un VSommet (nom, position, couleur)  (par exemple)
L'info associée aux arêtes est une combinaison de 2 couleurs : une de fond et une superficielle plus ou moins transparente (par exemple)
*/
/*
#include <iostream>
#include <sstream>
#include <string>
#include <SFML\Graphics\Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics/Font.hpp>
#include <Graphe.h>
#include <FenetreGrapheSFML.h>
#include <InfosGrapheDessin.h>
using namespace std;
using namespace sf;
*/
int main()
{
	bool testmillieur(int a);
	void deplacementRandom(Sommet<VSommet> *sommet, vector<Sommet<VSommet> *> s);
	/* chargement des polices de caractères */
	unsigned int magenta = Color::Magenta.toInteger();		// récupère la couleur Magenta au format nombre entier non signé
	unsigned int yellow = Color::Yellow.toInteger();
	unsigned int red = Color::Red.toInteger();
	unsigned int blue = Color::Blue.toInteger();
	Font font1, font2;
	string nomFichierFonte1 = "..\\mespolices\\abaddon.ttf";
	string nomFichierFonte2 = "..\\mespolices\\ActionManBoldItalic.ttf";
	bool ok = font1.loadFromFile(nomFichierFonte1);
	ok = font2.loadFromFile(nomFichierFonte2);

	char ch;

	Graphe<Peinture, VSommet> g1;	// création à vide
	Sommet<VSommet> *pacman, *f1, *f2, *f3;
	//pacman = g1.creeSommet((VSommet("Pacman", Vecteur2D(0.5,1.5), magenta)));
	pacman = g1.creeSommet(VSommet("pacman", Vecteur2D(0.5, 1.5), red));
	f1 = g1.creeSommet(VSommet("fantome", Vecteur2D(3.5, 1.5), blue));
	f2 = g1.creeSommet(VSommet("fantome", Vecteur2D(1.5, 2.5), blue));
	f3 = g1.creeSommet(VSommet("fantome", Vecteur2D(3.5, 3.5), blue));
	//	Sommet<VSommet> * s0, *s1, *s2, *s3, *s4,*s5,*s6,*s7,*s8,*s9,*s10,*s11,*s12,*s13,*s14,*s15,*s16,*s17,*s18,*s19,*s20,*s21,*s22,*s23,*s24,*s25,*s26;
	vector<Sommet<VSommet> *>  s;



	int i = 0;
	int ligne = 0;
	int colone = 0;
	for (i = 0;i < 36;i++) {


		if (((i + 1) % 6 == 0) || (i % 6 == 0) || (i <= 5) || (i > 29))
		{
			s.push_back(g1.creeSommet(VSommet("Mur", Vecteur2D((i % 6) - 0.5, (6 - i / 6) - 0.5), magenta)));
		}
		else {
			s.push_back(g1.creeSommet(VSommet("Soja", Vecteur2D((i % 6) - 0.5, (6 - i / 6) - 0.5), yellow)));
		}
		if (colone < 5) { colone++; }
		if (colone >= 5) { ligne++;colone = 0; }
	}

	//------------------ on insère des nouveaux sommets isolés --------------------


	//s0 = g1.creeSommet(VSommet("Kings Landing",Vecteur2D(100,700),magenta));
	//s1 = g1.creeSommet(VSommet("Winterfell",Vecteur2D(100,200),magenta));
	//s2 = g1.creeSommet(VSommet("DragonStone",Vecteur2D(400,400),magenta));
	//s3 = g1.creeSommet(VSommet("The wall",Vecteur2D(300,100),magenta));
	//s4 = g1.creeSommet(VSommet("Volantis",Vecteur2D(500,600),magenta));

   /*	s0 = g1.creeSommet(VSommet("Kings Landing", Vecteur2D(1, 1), magenta));
	s1 = g1.creeSommet(VSommet("Winterfell", Vecteur2D(1, 4), magenta));
	s2 = g1.creeSommet(VSommet("DragonStone", Vecteur2D(3, 3), magenta));
	s3 = g1.creeSommet(VSommet("The wall", Vecteur2D(2, 5), magenta));
	s4 = g1.creeSommet(VSommet("Volantis", Vecteur2D(5, 2), magenta));
	*/

	//VSommet *s;
	//s[0][0]= g1.creeSommet(VSommet("Mur", Vecteur2D(1, 1), magenta));

	/*s0 = g1.creeSommet(VSommet("Mur", Vecteur2D(1, 1),magenta));
	s1 = g1.creeSommet(VSommet("Mur",Vecteur2D(2,1),yellow));
	s2 = g1.creeSommet(VSommet("Mur", Vecteur2D(3, 1), yellow));
	s3 = g1.creeSommet(VSommet("Mur", Vecteur2D(4, 1), yellow));
	s4 = g1.creeSommet(VSommet("Mur", Vecteur2D(5, 1), yellow));
	s5 = g1.creeSommet(VSommet("Mur", Vecteur2D(1, 1), magenta));
	s6 = g1.creeSommet(VSommet("Soja", Vecteur2D(1, 2), magenta));
	s7 = g1.creeSommet(VSommet("Soja", Vecteur2D(2, 2), yellow));
	s8= g1.creeSommet(VSommet("Soja", Vecteur2D(3, 2), yellow));
	s9 = g1.creeSommet(VSommet("Soja", Vecteur2D(4, 2), yellow));
	s10 = g1.creeSommet(VSommet("Soja", Vecteur2D(5, 2), yellow));
	s11= g1.creeSommet(VSommet("Mur", Vecteur2D(6, 2), magenta));
	s12= g1.creeSommet(VSommet("Mur", Vecteur2D(1, 3), magenta));
	s13 = g1.creeSommet(VSommet("Soja", Vecteur2D(2, 3), yellow));
	s14= g1.creeSommet(VSommet("Soja", Vecteur2D(3, 3), yellow));
	s15 = g1.creeSommet(VSommet("Soja", Vecteur2D(4, 3), yellow));
	s16 = g1.creeSommet(VSommet("Soja", Vecteur2D(5, 3), magenta));
	s17 = g1.creeSommet(VSommet("Soja", Vecteur2D(1, 4), magenta));
	s18 = g1.creeSommet(VSommet("Soja", Vecteur2D(2, 4), yellow));
	s19 = g1.creeSommet(VSommet("Soja", Vecteur2D(3, 4), yellow));
	s20 = g1.creeSommet(VSommet("Soja", Vecteur2D(4, 4), yellow));
	s21 = g1.creeSommet(VSommet("Soja", Vecteur2D(5, 4), magenta));
	s22= g1.creeSommet(VSommet("Soja", Vecteur2D(1, 5), magenta));
	s23 = g1.creeSommet(VSommet("Soja", Vecteur2D(2, 5), yellow));
	s24 = g1.creeSommet(VSommet("Soja", Vecteur2D(3, 5), yellow));
	s25 = g1.creeSommet(VSommet("Soja", Vecteur2D(4, 5), yellow));
	s26 = g1.creeSommet(VSommet("Soja", Vecteur2D(5, 5), magenta));
	*/
	//----------------- on connecte certains sommets -------------------

	//Arete<Peinture, VSommet> * a0, *a1, *a2, *a3, *a4;

	unsigned int jaune0 = 0xDFFF00FF;   // jaune opaque
	unsigned int jaune1 = 0xDFFF00C0;   // jaune presque opaque
	unsigned int jaune2 = 0xDFFF0064;   // jaune un peu transparent
	unsigned int jaune3 = 0xDFFF0020;	// jaune presque transparent

	unsigned int tangerine0 = 0xFF7F00FF; // tangerine opaque
	unsigned int tangerine1 = 0xFF7F00DF; // tangerine presque opaque
	unsigned int tangerine2 = 0xFF7F00BF; // tangerine un peu transparent
	unsigned int tangerine3 = 0xFF7F0060; // tangerine presque transparent
	unsigned int tangerine4 = 0xFF7F0000; // tangerine  transparent


	//unsigned int jauneOpaque

	unsigned int turquoise = 0x00CED1FF;	// couleur turquoise opaque. préfixe 0x pour héxadécimal. format RGBA
	unsigned int vertCitron = 0x00FF00FF;
	// unsigned int turquoise = Color(0,206,209).toInteger(); // ou en utilisant les fonctionnalités de la classe Color de la librairie SFML
	vector<Arete<Peinture, VSommet> *>  a;
	int changerligne = 0;
	for (i = 0;i <= 29;i++) {
		if ((i + 1) % 6 == 0) { changerligne = 1; }
		else { changerligne = 0; }

		if (changerligne == 0) {
			a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 1]));
			s[i]->degre += 1;
			a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 6]));
			s[i]->degre += 1;
		}
		else {
			a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 6]));
			s[i]->degre += 1;

		}

		if (i < 18) {

			if (!testmillieur(i)) {
				if ((i + 2) % 6 == 0 || (i + 1) % 6 == 0) {
					a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 5]));
					s[i]->degre+=1;
				}
				else {
					a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 7]));
					s[i]->degre += 1;
				}
			}
		}
		else {
			if (changerligne == 0) {
				if ((i - 1) % 6 == 0 || (i - 2) % 6 == 0 || (i - 3) % 6 == 0) {
					a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 5]));
					s[i]->degre += 1;
					if (testmillieur(i)) {
						a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 7]));
						s[i]->degre += 1;
					}
				}

				else {
					if ((i != 24) && (i != 18))	a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 7]));
					s[i]->degre += 1;
				}
			}
		}



	}

	for (i;i < 35;i++) {
		a.push_back(g1.creeArete(Peinture(vertCitron, tangerine0), s[i], s[i + 1]));
		s[i]->degre += 1;
	}
	/*a0 = g1.creeArete(Peinture(vertCitron, tangerine0), s2, s1);
	a1 = g1.creeArete(Peinture(vertCitron, tangerine1), s3, s2);
	a2 = g1.creeArete(Peinture(vertCitron, tangerine2), s1, s3);
	a3 = g1.creeArete(Peinture(vertCitron, tangerine3), s0, s1);
	a4 = g1.creeArete(Peinture(vertCitron, tangerine4), s0, s4);
	*/
	//------------------ on dessine le graphe ----------------

	cout << "le graphe créé g1 est :" << endl << g1 << endl;
	//cin >> ch;

	string titre("The seven kingdoms");
	int largeur = 1500, hauteur = 1000;
	//Vecteur2D  coinBG(0,hauteur), coinHD(largeur,0);

	Vecteur2D  coinBG(-0.8, -0.8), coinHD(6, 6);

	unsigned int fondCarte = 0xEFEFEFFF;	// sorte de gris clair ~= étain pur

	//FenetreGrapheSFML fenetreGraphe( titre, fondCarte, coinBG, coinHD, largeur, hauteur, font1);
	FenetreGrapheSFMLAvecAxesRepereMonde fenetreGraphe(titre, fondCarte, coinBG, coinHD, largeur, hauteur, font1, font2);
	ok = g1.dessine(fenetreGraphe);
	cout << "123";
	cout << "graphe dessiné ? " << (ok ? "succès" : "échec") << endl;
	cout << "123";
	fenetreGraphe.fenetre.display();
	////////////////////////////
	




	sf::Clock clock;
	clock.restart();
	double lastTime = clock.getElapsedTime().asMilliseconds();
	double delta = 0;
	//boucle infinie de contrôle des évènements de la fenêtre

	///////////////////////////////////////////////////////////
	while (fenetreGraphe.fenetre.isOpen())
	{
		
		double newTime = clock.getElapsedTime().asMilliseconds();
		delta += newTime - lastTime;
		if (delta > 1000) {
			clock.restart();
		//	cout << "degre"<<f1->degre;
		//	cout << f2->degre;
		//	cout << f3->degre;
			deplacementRandom(f1,s);
			deplacementRandom(f2,s);
			deplacementRandom(f3,s);
			delta = 0;
				}
		
			
		else {
			lastTime = newTime;
		}


		Event event;
		while (fenetreGraphe.fenetre.pollEvent(event))
		{

			if (event.type == Event::Closed) /*(event.type == Event::EventType::Closed)*/
				fenetreGraphe.fenetre.close();
			if (event.type == Event::KeyPressed)
			{
				Event::KeyEvent touche = event.key;
				Keyboard::Key codeTouche = touche.code;
				cout << "touche clavier tapee : " << (char)codeTouche << (int)codeTouche << endl;
				if (codeTouche == Keyboard::Z) {
					//g1.lSommets->v->v.p.x -= 1;
					//g1.lSommets->v->v.p.y -= 1;
					pacman->v.p.y -= 1;
					pacman->v.p.x -= 1;
				}
				if (codeTouche == Keyboard::S) {
				//	g1.lSommets->v->v.p.x -= 1;
					pacman->v.p.y -= 1;
				}
				if (codeTouche == Keyboard::C) {
					//g1.lSommets->v->v.p.x += 1;
					//g1.lSommets->v->v.p.y -= 1;
					pacman->v.p.y -= 1;
					pacman->v.p.x += 1;
				}
				if (codeTouche == Keyboard::A) {
					//g1.lSommets->v->v.p.y -= 1;
					pacman->v.p.y -= 1;
				}
				if (codeTouche == Keyboard::D) {
					//g1.lSommets->v->v.p.x += 1;
					pacman->v.p.x += 1;
				}
				if (codeTouche == Keyboard::Q) {
					//g1.lSommets->v->v.p.x -= 1;
					//g1.lSommets->v->v.p.y += 1;
					pacman->v.p.y += 1;
					pacman->v.p.x -= 1;
				
				}
				if (codeTouche == Keyboard::W) {
					//g1.lSommets->v->v.p.y += 1;
				 	pacman->v.p.y += 1;
				
				//	ok = g1.dessine(fenetreGraphe);
				}
				if (codeTouche == Keyboard::E) {
					//g1.lSommets->v->v.p.x += 1;
					//g1.lSommets->v->v.p.y += 1;
					pacman->v.p.y += 1;
					pacman->v.p.x += 1;
				}
			}
		}
		//window.clear();
		ok = g1.dessine(fenetreGraphe);
		fenetreGraphe.fenetre.display();
	}
 
	return 0;
}

bool testmillieur(int i) {
	switch (i) {
	case 3: return true;break;
	case 15:return true;break;
	case 9:return true;break;
	case 21:return true;break;
	case 27:return true;break;
	case 33:return true;break;


	}
	return false;
}

void deplacementRandom(Sommet<VSommet> *sommet, vector<Sommet<VSommet> *>s) {
	 int r;
	//int r = rand() % sommet->degre + 1;
	//int r = rand() % sommet->degre + 1;
	 if (sommet->v.p.x == s[15]->v.p.x) { r = rand() % 8 + 1; }
	 else { r = rand() % 6 + 1; }
	if ((sommet->v.p.x < 2.5 && sommet->v.p.y > 2.5) || (sommet->v.p.x > 2.5 && sommet->v.p.y < 2.5)) {
		switch (r) {
		case 1: sommet->v.p.x -= 1;
			break;
		case 2: sommet->v.p.x -= 1;
			sommet->v.p.y += 1;
			break;
		case 3: sommet->v.p.y += 1;
			break;
		case 4: sommet->v.p.x += 1;
			break;
		case 5: sommet->v.p.x += 1;
			sommet->v.p.y -= 1;
			break;
		case 6: sommet->v.p.y -= 1;
			break;
		}
	}
	else {
		if ((sommet->v.p.x < 2.5 && sommet->v.p.y < 2.5) || (sommet->v.p.x > 2.5 && sommet->v.p.y > 2.5)) {
			switch (r) {
			case 1: sommet->v.p.x -= 1;
				break;
			case 2: sommet->v.p.x -= 1;
				sommet->v.p.y -= 1;
				break;
			case 3: sommet->v.p.y += 1;
				break;
			case 4: sommet->v.p.x += 1;
				break;
			case 5: sommet->v.p.x += 1;
				sommet->v.p.y += 1;
				break;
			case 6: sommet->v.p.y -= 1;
				break;
			}
		}
		else {
			if (sommet->v.p.x < 2.5 && sommet->v.p.y == 2.5) {
				switch (r) {
				case 1: sommet->v.p.x -= 1;
					break;
				case 2: sommet->v.p.x -= 1;
					sommet->v.p.y += 1;
					break;
				case 3: sommet->v.p.y += 1;
					break;
				case 4: sommet->v.p.x += 1;
					break;
				case 5: sommet->v.p.x -= 1;
					sommet->v.p.y -= 1;
					break;
				case 6: sommet->v.p.y -= 1;
					break;
				}
			}
			else {
				if (sommet->v.p.x > 2.5 && sommet->v.p.y == 2.5) {
					switch (r) {
					case 1: sommet->v.p.x -= 1;
						break;
					case 2: sommet->v.p.x += 1;
						sommet->v.p.y += 1;
						break;
					case 3: sommet->v.p.y += 1;
						break;
					case 4: sommet->v.p.x += 1;
						break;
					case 5: sommet->v.p.x += 1;
						sommet->v.p.y -= 1;
						break;
					case 6: sommet->v.p.y -= 1;
						break;
					}
				}
				else {
					if (sommet->v.p.x < 2.5 && sommet->v.p.y == 2.5) {
						switch (r) {
						case 1: sommet->v.p.x -= 1;
							break;
						case 2: sommet->v.p.x += 1;
							sommet->v.p.y += 1;
							break;
						case 3: sommet->v.p.y += 1;
							break;
						case 4: sommet->v.p.x += 1;
							break;
						case 5: sommet->v.p.x -= 1;
							sommet->v.p.y -= 1;
							break;
						case 6: sommet->v.p.y -= 1;
							break;
						case 7: sommet->v.p.x -= 1;
							sommet->v.p.y += 1;
							break;
						case 8: sommet->v.p.x += 1;
							sommet->v.p.y -= 1;
							break;
						}
					}
				}
			}
		}
	}	if ((sommet->v.p.x < 2.5 && sommet->v.p.y > 2.5) || (sommet->v.p.x > 2.5 && sommet->v.p.y < 2.5)) {
		switch (r) {
		case 1: sommet->v.p.x -= 1;
			break;
		case 2: sommet->v.p.x -= 1;
			sommet->v.p.y += 1;
			break;
		case 3: sommet->v.p.y += 1;
			break;
		case 4: sommet->v.p.x += 1;
			break;
		case 5: sommet->v.p.x += 1;
			sommet->v.p.y -= 1;
			break;
		case 6: sommet->v.p.y -= 1;
			break;
		}
	}
	else {
		if ((sommet->v.p.x < 2.5 && sommet->v.p.y < 2.5) || (sommet->v.p.x > 2.5 && sommet->v.p.y > 2.5)) {
			switch (r) {
			case 1: sommet->v.p.x -= 1;
				break;
			case 2: sommet->v.p.x -= 1;
				sommet->v.p.y -= 1;
				break;
			case 3: sommet->v.p.y += 1;
				break;
			case 4: sommet->v.p.x += 1;
				break;
			case 5: sommet->v.p.x += 1;
				sommet->v.p.y += 1;
				break;
			case 6: sommet->v.p.y -= 1;
				break;
			}
		}
		else {
			if (sommet->v.p.x < 2.5 && sommet->v.p.y == 2.5) {
				switch (r) {
				case 1: sommet->v.p.x -= 1;
					break;
				case 2: sommet->v.p.x -= 1;
					sommet->v.p.y += 1;
					break;
				case 3: sommet->v.p.y += 1;
					break;
				case 4: sommet->v.p.x += 1;
					break;
				case 5: sommet->v.p.x -= 1;
					sommet->v.p.y -= 1;
					break;
				case 6: sommet->v.p.y -= 1;
					break;
				}
			}
			else {
				if (sommet->v.p.x > 2.5 && sommet->v.p.y == 2.5) {
					switch (r) {
					case 1: sommet->v.p.x -= 1;
						break;
					case 2: sommet->v.p.x += 1;
						sommet->v.p.y += 1;
						break;
					case 3: sommet->v.p.y += 1;
						break;
					case 4: sommet->v.p.x += 1;
						break;
					case 5: sommet->v.p.x += 1;
						sommet->v.p.y -= 1;
						break;
					case 6: sommet->v.p.y -= 1;
						break;
					}
				}
				else {
					if (sommet->v.p.x < 2.5 && sommet->v.p.y == 2.5) {
						switch (r) {
						case 1: sommet->v.p.x -= 1;
							break;
						case 2: sommet->v.p.x += 1;
							sommet->v.p.y += 1;
							break;
						case 3: sommet->v.p.y += 1;
							break;
						case 4: sommet->v.p.x += 1;
							break;
						case 5: sommet->v.p.x -= 1;
							sommet->v.p.y -= 1;
							break;
						case 6: sommet->v.p.y -= 1;
							break;
						case 7: sommet->v.p.x -= 1;
							sommet->v.p.y += 1;
							break;
						case 8: sommet->v.p.x += 1;
							sommet->v.p.y -= 1;
							break;
						}
					}
				}
			}
		}
	}
}