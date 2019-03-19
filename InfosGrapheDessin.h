#ifndef INFOSGRAPHEDESSIN_H_INCLUDED
#define INFOSGRAPHEDESSIN_H_INCLUDED

#include <SFML\Graphics\Color.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "Vecteur2D.h"

/**

Classes VSommet et Peinture : elles sont utilisées dans TestDessinGraphe pour dessiner un graphe.


informations associée ?un sommet : nom, position, couleur
sert ?tester l'opération "dessiner un graphe"

VSommet comme "valeur associée ?un sommet"

*/
class VSommet
{
public:
constexpr static  int rayonDisquePixels = 10;
constexpr static unsigned int couleurBord = 0xA10684FF; // couleur violine opaque
string nom;
Vecteur2D p;		  // position
unsigned int couleur; // couleur au format rgba


/**
par défaut, la couleur d'un sommet est rouge opaque
*/
VSommet( const string & nom, const Vecteur2D & p, const unsigned int couleur = 0xFF0000FF) : nom(nom), p(p), couleur(couleur) {}

virtual
operator string () const { ostringstream o; o <<"( " << nom <<", " << p << ", " << couleur <<")"; return o.str();}

friend ostream & operator << ( ostream & o, const VSommet & vSommet) { return o << (string) vSommet;}
};

/**
Peinture  ?2 couches : informations associées ?une arête pour la dessiner avec des dégradés de couleur
sert ?tester l'opération "dessiner un graphe"

*/
class Peinture
{
public:
unsigned int fond;		// couleur du fond (ou sous-couche de peinture)
unsigned int devant;	// couleur masquant  la couleur du fond. ou dernière couche de peinture.
						// Elle masque pas du tout, partiellement ou entièrement la couleur du fond
Peinture ( const unsigned int couleurFond, const unsigned int couleurDevant) : fond(couleurFond), devant( couleurDevant) {}

virtual operator string () const { ostringstream o; o <<"( " << fond <<", " << devant <<")"; return o.str();}

friend ostream & operator << ( ostream & o, const Peinture & peinture) { return o << (string) peinture;}
};


#endif // INFOSGRAPHEDESSIN_H_INCLUDED
