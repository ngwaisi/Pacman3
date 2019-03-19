/*

Test de l'opération dessiner un graphe planaire

L'info associée aux sommets est un VSommet (nom, position, couleur)  (par exemple)
L'info associée aux arêtes est une combinaison de 2 couleurs : une de fond et une superficielle plus ou moins transparente (par exemple)

*/
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


int main()
{
/* chargement des polices de caractères */

Font font1, font2;
string nomFichierFonte1 = "..\\mespolices\\abaddon.ttf";
string nomFichierFonte2 = "..\\mespolices\\ActionManBoldItalic.ttf";
bool ok = font1.loadFromFile(nomFichierFonte1);
ok = font2.loadFromFile(nomFichierFonte2);

char ch;

Graphe<Peinture,VSommet> g1;	// création à vide

Sommet<VSommet> * s0, *s1, *s2, *s3, *s4;

//------------------ on insère des nouveaux sommets isolés --------------------

unsigned int magenta = Color::Magenta.toInteger();		// récupère la couleur Magenta au format nombre entier non signé

//s0 = g1.creeSommet(VSommet("Kings Landing",Vecteur2D(100,700),magenta));
//s1 = g1.creeSommet(VSommet("Winterfell",Vecteur2D(100,200),magenta));
//s2 = g1.creeSommet(VSommet("DragonStone",Vecteur2D(400,400),magenta));
//s3 = g1.creeSommet(VSommet("The wall",Vecteur2D(300,100),magenta));
//s4 = g1.creeSommet(VSommet("Volantis",Vecteur2D(500,600),magenta));

s0 = g1.creeSommet(VSommet("Kings Landing",Vecteur2D(1,1),magenta));
s1 = g1.creeSommet(VSommet("Winterfell",Vecteur2D(1,4),magenta));
s2 = g1.creeSommet(VSommet("DragonStone",Vecteur2D(3,3),magenta));
s3 = g1.creeSommet(VSommet("The wall",Vecteur2D(2,5),magenta));
s4 = g1.creeSommet(VSommet("Volantis",Vecteur2D(5,2),magenta));


//----------------- on connecte certains sommets -------------------

Arete<Peinture,VSommet> * a0, * a1, *a2, *a3, *a4;

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

a0 = g1.creeArete(Peinture(vertCitron,tangerine0),s2,s1);
a1 = g1.creeArete(Peinture(vertCitron,tangerine1),s3,s2);
a2 = g1.creeArete(Peinture(vertCitron,tangerine2),s1,s3);
a3 = g1.creeArete(Peinture(vertCitron,tangerine3),s0,s1);
a4 = g1.creeArete(Peinture(vertCitron,tangerine4),s0,s4);

//------------------ on dessine le graphe ----------------

cout <<"le graphe créé g1 est :" << endl << g1 << endl;
cin >> ch;

string titre("The seven kingdoms");
int largeur = 800, hauteur = 400;
//Vecteur2D  coinBG(0,hauteur), coinHD(largeur,0);

Vecteur2D  coinBG(-0.5,-0.5), coinHD(6,6);

unsigned int fondCarte = 0xEFEFEFFF;	// sorte de gris clair ~= étain pur

//FenetreGrapheSFML fenetreGraphe( titre, fondCarte, coinBG, coinHD, largeur, hauteur, font1);
FenetreGrapheSFMLAvecAxesRepereMonde fenetreGraphe( titre, fondCarte, coinBG, coinHD, largeur, hauteur, font1, font2);
ok = g1.dessine(fenetreGraphe);
cout <<"graphe dessiné ? "  << (ok  ? "succès":"échec") << endl;
fenetreGraphe.fenetre.display();

//boucle infinie de contrôle des évènements de la fenêtre
while( fenetreGraphe.fenetre.isOpen())
	 {
	 Event event;
	 while(fenetreGraphe.fenetre.pollEvent(event))
		  {

		  if (event.type == Event::Closed) /*(event.type == Event::EventType::Closed)*/
			 fenetreGraphe.fenetre.close();
		  }

	 }
return 0;
}
