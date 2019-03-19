#ifndef INFOSGRAPHEDESSIN_H_INCLUDED
#define INFOSGRAPHEDESSIN_H_INCLUDED

#include <SFML\Graphics\Color.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "Vecteur2D.h"

/**

Classes VSommet et Peinture : elles sont utilis�es dans TestDessinGraphe pour dessiner un graphe.


informations associ�e ?un sommet : nom, position, couleur
sert ?tester l'op�ration "dessiner un graphe"

VSommet comme "valeur associ�e ?un sommet"

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
par d�faut, la couleur d'un sommet est rouge opaque
*/
VSommet( const string & nom, const Vecteur2D & p, const unsigned int couleur = 0xFF0000FF) : nom(nom), p(p), couleur(couleur) {}

virtual
operator string () const { ostringstream o; o <<"( " << nom <<", " << p << ", " << couleur <<")"; return o.str();}

friend ostream & operator << ( ostream & o, const VSommet & vSommet) { return o << (string) vSommet;}
};

/**
Peinture  ?2 couches : informations associ�es ?une ar�te pour la dessiner avec des d�grad�s de couleur
sert ?tester l'op�ration "dessiner un graphe"

*/
class Peinture
{
public:
unsigned int fond;		// couleur du fond (ou sous-couche de peinture)
unsigned int devant;	// couleur masquant  la couleur du fond. ou derni�re couche de peinture.
						// Elle masque pas du tout, partiellement ou enti�rement la couleur du fond
Peinture ( const unsigned int couleurFond, const unsigned int couleurDevant) : fond(couleurFond), devant( couleurDevant) {}

virtual operator string () const { ostringstream o; o <<"( " << fond <<", " << devant <<")"; return o.str();}

friend ostream & operator << ( ostream & o, const Peinture & peinture) { return o << (string) peinture;}
};


#endif // INFOSGRAPHEDESSIN_H_INCLUDED
