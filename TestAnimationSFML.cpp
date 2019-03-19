#include <time.h>
#include <chrono>
#include <ratio>
#include<stdlib.h>
#include<string>
#include<SFML/GRAPHICS/RenderWIndow.hpp>
#include<SFML/GRAPHICS/CircleShape.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include<AlgebreLineaire.h>
#include<Erreur.h>
#include<Reels.h>
#include <Vecteur2D.h>
#include "GestionChrono.h"

using namespace std;
using namespace std::chrono;
using namespace sf;



int main()
{
//constexpr double PI = 3.1416;
cout <<"essai d'animation : un objet d�crit une trajectoire circulaire" << endl;
Vecteur2D diagonale(400,250);		// diagonale principale de la fen�tre � cr�er
int hauteur, largeur;
diagonale.arrondit(hauteur,largeur);
sf::RenderWindow maFenetre(sf::VideoMode(hauteur,largeur),"essai d'animation : un objet d�crit une trajectoire circulaire");
// la fen�tre est cr��e et rendue visible

//----------------------- param�tres cont�lant la trajectoire circulaire ------------
double  alfa0, omega;			// angle initial, vitesse angulaire
double rayon, t, t0, deltaT;	// rayon de la trajectoire circulaire, temps, temps initial, delta de temps entre 2 mises � jour de la sc�ne
								// le temps est mesur� en s.
Vecteur2D centre, u, u0;		// centre de la trajectoire circuaire, vecteur unitaire sortant sur un rayon de la trajectoire
								// vecteur unitaire  initial sortant sur un rayon de la trajectoire

//------------- initialisation trajectoire initiale ---------------------

alfa0 = 0;
omega = Reels::PI/10; // vitesse angulaire : 3 tours /min
t0 = 0;
centre = 0.5*diagonale;							// le centre de la trajectoire est le centre de la sc�ne
rayon = 0.25*abs(min(diagonale.x,diagonale.y));	// le rayon de la trajectoire est le 1/4 du  plus petit c�t� de la fen�tre
u0 = Vecteur2D(cos(alfa0),sin(alfa0));

//------------- gestion de l'acc�l�ration angulaire pilot�e par l'utilisateur
double k,k1; // facteur d'acc�l�ration angulaire, facteur de freinage : k1 = 1/k
{
double taux = 0.2;	// la vitesse angulaire augmente de 20% � chaque frappe de la touche Up, diminue de 20% � chaque frappe de la touche Down
k = 1+taux; k1 = 1/k;
}

//--------------------- boucle graphique ---------------

steady_clock::time_point maintenant;	// sert � calculer le temps �coul� entre 2 tours de la boucle for

for( t = t0, u = u0, maintenant = steady_clock::now(); maFenetre.isOpen();   )
   {
   Event event;
   while(maFenetre.pollEvent(event))
		{
		if (event.type == Event::EventType::Closed)
		   maFenetre.close();
		if (event.type == Event::KeyPressed)			// if (event.type == Event/*::EventType*/::KeyPressed)
		   {
		   Event::KeyEvent touche = event.key;
		   Keyboard::Key codeTouche = touche.code;
		   cout <<"touche clavier tap�e : " << (char)codeTouche << (int)codeTouche << endl;
		   if (codeTouche == Keyboard::Subtract)
			  omega = -omega;						// on inverse le sens de rotation
		   if (codeTouche == Keyboard::Up)			// la rotation acc�l�re
			  omega *= k;
		   if (codeTouche == Keyboard::Down)		// la rotation ralentit
			  omega *= k1;
		   }
		}

   // mise � jour de l'animation, calculs ...
   steady_clock::time_point avant = maintenant;
   maintenant = steady_clock::now();
   deltaT = duree(avant,maintenant);
   t += deltaT;																	//cerr <<"deltaT = " << deltaT << endl;
   double deltaAlfa = omega*deltaT;												//cerr <<"deltaAlfa = " << deltaAlfa << endl;// variation angulaire correspondant � deltaT
   Vecteur2D rotation(cos(deltaAlfa),sin(deltaAlfa));	// calcul de la rotation � appliquer : e^(ideltaAlfa) : nombre complexe
   u ^= rotation;										// mise � jour du vecteur rayon
   Vecteur2D P = centre + rayon*u;						// on cr�e un point P appartenant au cercle de centre "centre" et de rayon "rayon"

   // effacement de la fen�tre en noir

   maFenetre.clear(sf::Color::Black);

   // c'est ici qu'on dessine tout

   // cr�ation d'un petit disque correspondant au point P
   float rayonDisque = 10;
   CircleShape disque(rayonDisque);
   disque.setFillColor(Color::Magenta);
   float epaisseurBord = (float)(0.1*rayonDisque);
   disque.setOutlineThickness(epaisseurBord);
   disque.setOutlineColor(Color::Green);
   disque.setPosition((float)P.x, (float)P.y);

    // window.draw(...);

   maFenetre.draw(disque);

	// fin de la frame courante, affichage de tout ce qu'on a dessin�

   maFenetre.display();

   }

char ch;
cin >> ch;
return 0;
}
