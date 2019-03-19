#ifndef FENETREGRAPHESFMLASTAR_H
#define FENETREGRAPHESFMLASTAR_H

#pragma once

#include "FenetreGrapheSFML.h"
#include "InfoSommet.h"
#include "InfoArete.h"
#include "Vecteur2D.h"
using namespace sf;
using namespace std;


//---------------------------------------dessine le cas particulier de InfoSommet et InfoArete ------------------------------

/**
Dessine un sommet du graphe. Exemples :  nom, couleur, informations associées, etc.
renvoie true en cas de succès, false en cas d'échec
On suppose que les coordonnées du sommet sont définies par rapport au repère du monde
*/
template <>
bool FenetreGrapheSFML::dessine<InfoSommet>(const Sommet<InfoSommet> * sommet)
{
Vecteur2D deltaTextePixels (0.8*VSommet::rayonDisquePixels,VSommet::rayonDisquePixels);
return dessinePetitRond(this->fenetre, this->t, sommet->v.vSommet, this->font,deltaTextePixels);
}

/**
Dessine l'arête (début->fin) en utilisant la couleur "couleur"
renvoie true en cas de succès, false en cas d'échec
On suppose que les coordonnées des sommets sont définies par rapport au repère du monde
*/
template <>
bool FenetreGrapheSFML::dessine<InfoSommet>(const Sommet<InfoSommet> * debut, const Sommet<InfoSommet> * fin, unsigned int couleur)
{
unsigned int epaisseurAretePixels = 1;
return dessineSegment( this->fenetre, this->t, couleur, debut->v.vSommet.p, fin->v.vSommet.p,epaisseurAretePixels);
}

/**
Dessine un arête du graphe. Exemples :  nom, couleur, informations associées, etc.
renvoie true en cas de succès, false en cas d'échec
On suppose que les coordonnées des sommets sont définies par rapport au repère du monde
*/
template <>
bool FenetreGrapheSFML::dessine<InfoArete,InfoSommet>(const Arete<InfoArete,InfoSommet> * arete)
{
unsigned int epaisseurAretePixels = 4;
return dessineSegment( this->fenetre, this->t, arete->v.couleur, arete->debut->v.vSommet.p, arete->fin->v.vSommet.p,epaisseurAretePixels);
}



#endif // INFOSGRAPHEDESSINASTAR_H_INCLUDED
