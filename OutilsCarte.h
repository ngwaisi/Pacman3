#ifndef OUTILSCARTE_H
#define OUTILSCARTE_H
 


#pragma once

#include "AlgebreLineaire.h"
#include "Sommet.h"
#include "InfoSommet.h"
#include "InfoArete.h"

#include "Arete.h"

#include "Graphe.h"

using namespace std;

//#include "AStarT.h"

/**
sert d'intermédiaire entre A* et une carte routière. Définit pour une carte routière, toutes les méthodes que
réclame l'algo A*.
L'information inscrite dans une arête est une InfoArete qui contient une couleur et la longueur de l'arête
L'information inscrite dans un sommet est une InfoSommet qui contient 2 attributs : VSommet et InfoAStar.

Par conséquent :

Une carte routière est un Graphe <InfoArete, InfoSommet >

A savoir, A* réclame les méthodes suivantes :

libereToutSommet(graphe) : met l'état de tous les sommets à LIBRE et tous les liens père à NULL
listeVoisins(sommet,graphe) : renvoie une liste de paires (voisin, coût entre sommet et voisin)
pere(sommet)
etat(sommet)
c(sommet)
g(sommet)
h(sommet)
estFinal(sommet)

*/


class OutilsCarte
{
public:
static double distance( const Sommet<InfoSommet> * s1, const Sommet<InfoSommet> * s2);
static Arete<InfoArete, InfoSommet> *  creeArete(Sommet<InfoSommet> * sA, Sommet<InfoSommet> * sB,Graphe<InfoArete, InfoSommet> & graphe);
static void libereToutSommet(Graphe<InfoArete, InfoSommet> & graphe);
static double hh(const Sommet<InfoSommet> * s);
static PElement< pair<Sommet<InfoSommet>*,double> > * listeVoisins(const Sommet<InfoSommet> * s, const Graphe<InfoArete, InfoSommet> & graphe);

static Sommet<InfoSommet> *  pere( const Sommet<InfoSommet> * sommet);
static Sommet<InfoSommet> * & pere( Sommet<InfoSommet> * sommet);
static int & etat( Sommet<InfoSommet> * sommet);
static double & c( Sommet<InfoSommet> * sommet);
static double & h( Sommet<InfoSommet> * sommet);
static double g( const Sommet<InfoSommet> * sommet);
static double & g( Sommet<InfoSommet> * sommet);

static bool estFinal(const Sommet<InfoSommet> * sommet);

static Sommet<InfoSommet> * cible;
};

void libereToutSommet(Graphe<InfoArete, InfoSommet> & graphe);
PElement< pair<Sommet<InfoSommet>*,double> > * listeVoisins(const Sommet<InfoSommet> * s, const Graphe<InfoArete, InfoSommet> & graphe);

Sommet<InfoSommet> *  pere( const Sommet<InfoSommet> * sommet);
Sommet<InfoSommet> * & pere( Sommet<InfoSommet> * sommet);
int & etat( Sommet<InfoSommet> * sommet);
double & c( Sommet<InfoSommet> * sommet);
double & h( Sommet<InfoSommet> * sommet);
double g( const Sommet<InfoSommet> * sommet);
double & g( Sommet<InfoSommet> * sommet);

bool estFinal(const Sommet<InfoSommet> * sommet);


/**
compte le nombre de maillons de la liste chaînée "pere" dont le maillon de tête est "tête".
*/
int longueurChemin(const Sommet<InfoSommet>* tete);

const Sommet<InfoSommet> * dernierMaillon(const Sommet<InfoSommet>* tete);
#endif // !