#ifndef ASTART_H
#define ASTART_H

#pragma once
#include <utility>

#include"PElement.h"

/*
Explication de mes motivations qui ont conduit à cette solution pour A*.

L'algo A* doit être indépendant de :
1) la manière dont est représenté un graphe
2) le thème représenté par le graphe (bref, du domaine d'application du graphe)
3) De la manière dont est représenté un sommet

De plus, on veut que l'algo soit optimisé (en temps et en espace)

Il reste une opération qui peut être optimisée : l'insertion en ordre sur la liste des ouverts : ici elle est O(n) alors qu'elle pourrait être faite en O(log n) en remplaçant les
listes linéaires par des arbres binaires à hauteur équilibrée


Notons dep, le sommet de départ et cib, le sommet cible trouvé.
A*, pour fonctionner, a besoin pour tout sommet s des infos suivantes :
c : coût réel du chemin de dep à s
h : estimation (heuristique) du coût du chemin de s à cib
g = c+h : estimation du coût du chemin de dep à cib passant par s
pere : pointeur vers le sommet-père de s
etat : état du sommet : fermé, ouvert ou libre
Je ne veux pas faire de ces infos des fonctions virtuelles : c'est trop coûteux et mal adapté : les fonctions virtuelles conviennent bien pour les pbs où les données sont hétérogènes
mais ce n'est pas le cas d'un graphe

*/



/**
suppose que pour tout s sommet de graphe, on a:
s.etat = LIBRE

suppose que les fonctions coût et  h sont toujours >= 0
*/

template <class Graphe, class Sommet>
class AStarT
{
public:

static bool estPlusPetitOuEgal(const Sommet * sommet1, const Sommet * sommet2)
{
return g(sommet1) <= g(sommet2);
}



/**

recherche  dans graphe le plus court chemin de départ à cible par l'algo A*.
en cas de succès, les liens "père" des sommets indiquent le chemin à suivre en partant de cible vers départ.
le père de départ vaut toujours NULL en sortie (c'est la racine du chemin ou bien encore la fin de la liste chaînée "père")

retourne vrai si succès et faux si échec

suppose que tout sommet s du graphe
dispose des attributs suivants publics :
int etat (peut prendre l'une des 3 valeurs suivantes : LIBRE, OUVERT ou FERMé)
pere : Sommet * pere
double c;		// coût réel entre départ et s
double h;		// estimation du coût entre s et cible
double g;		// g == c+h

suppose que la méthode listeVoisins(sommet,graphe) retourne la liste des paires (voisin, coût de l'arête sommet-voisin)

hh est l'heuristique à appliquer entre 2 sommets quelconques du graphe

*/
static bool aStar1Cible(Graphe & graphe, Sommet * depart, Sommet * cible,
			double (*hh)(const Sommet * s1, const Sommet * s2)/*,
			PElement< pair<Sommet*,double> > * (*listeVoisins)(const Sommet * s, const Graphe & graphe),
			void (*libereToutSommet)(Graphe & graphe)*/)
{
libereToutSommet(graphe); // met tous les sommets du graphe à LIBRE et tous les liens-pere à NULL
PElement<Sommet> * Ouverts;

pere(depart) = NULL; c(depart) = 0; // depart->h = h(depart,cible); depart->g = depart->c + depart->h; // ces 2 dernières affectations sont inutiles

Ouverts = new PElement<Sommet>(depart,NULL); etat(depart) = OUVERT;

while(Ouverts)
	{
	Sommet  * s =PElement<Sommet>::depiler(Ouverts); etat(s) = FERME;

	if (s == cible) { PElement<Sommet>::efface1(Ouverts); return true;}

	PElement< pair<Sommet*,double> > * listeDesVoisins = listeVoisins(s, graphe);
	PElement< pair<Sommet*,double> > * l;

	for( l = listeDesVoisins; l; l = l->s)		// on parcourt les voisins de s
		{
		Sommet * v = l->v->first;	// v est le voisin courant de s

		double nouveauCout = c(s) + l->v->second;			//l->v->second est le coût de l'arête s - v

		if (etat(v) == LIBRE)
			{
			h(v) = hh(v,cible);
			miseAJourVoisin( v, s, nouveauCout, Ouverts);
			}
		else			// v est Fermé ou Ouvert

			if ( nouveauCout < c(v))
				{
				if (etat(v) == OUVERT)
					PElement< Sommet>::retire(v,Ouverts);

				miseAJourVoisin( v, s, nouveauCout, Ouverts);

				}				// if (nouveauCout < v->c)
		}			// for

	PElement< pair<Sommet*,double> >::efface2(listeDesVoisins);
	}	// while (Ouverts)

return false; // échec

}	// aStar1Cible

/**

recherche  dans graphe le plus court chemin de départ à un état final par l'algo A*.
en cas de succès, les liens "père" des sommets indiquent le chemin à suivre en partant du sommet-cible trouvé vers départ.
le père de départ vaut toujours NULL en sortie (c'est la racine du chemin ou bien encore la fin de la liste chaînée "père")

retourne un pointeur sur le sommet-cible trouvé  (le 1er sommet rencontré qui satisfait estFinal()) si succès et NULL si échec

suppose que tout sommet s du graphe
dispose des attributs suivants publics :
int etat (peut prendre l'une des 3 valeurs suivantes : LIBRE, OUVERT ou FERMé)
pere : Sommet * pere
double c;		// coût réel entre départ et s
double h;		// estimation du coût entre s et cible
double g;		// g == c+h

suppose que la méthode listeVoisins(sommet,graphe) retourne la liste des paires (voisin, coût de l'arête sommet-voisin)

hh est l'heuristique à appliquer entre 1 sommet quelconque du graphe et un état final

bool estFinal(const Sommet * s) est une méthode indiquant si le sommet correspond à un état final

*/
static Sommet * aStar(Graphe & graphe, Sommet * depart,
			double (*hh)(const Sommet * s)/*,
			PElement< pair<Sommet*,double> > * (*listeVoisins)(const Sommet * s, const Graphe & graphe),
			void (*libereToutSommet)(Graphe & graphe)*/)
{
libereToutSommet(graphe); // met tous les sommets du graphe à LIBRE et tous les liens-pere à NULL
PElement<Sommet> * Ouverts;

pere(depart) = NULL; c(depart) = 0; // depart->h = h(depart,cible); depart->g = depart->c + depart->h; // ces 2 dernières affectations sont inutiles

Ouverts = new PElement<Sommet>(depart,NULL); etat(depart) = OUVERT;

while(Ouverts)
	{
	Sommet  * s =PElement<Sommet>::depiler(Ouverts); etat(s) = FERME;

	if (estFinal(s)) { PElement<Sommet>::efface1(Ouverts); return s;}

	PElement< pair<Sommet*,double> > * listeDesVoisins = listeVoisins(s, graphe);
	PElement< pair<Sommet*,double> > * l;

	for( l = listeDesVoisins; l; l = l->s)		// on parcourt les voisins de s
		{
		Sommet * v = l->v->first;	// v est le voisin courant de s

		double nouveauCout = c(s) + l->v->second;			//l->v->second est le coût de l'arête s - v

		if (etat(v) == LIBRE)
			{
			h(v) = hh(v);
			miseAJourVoisin( v, s, nouveauCout, Ouverts);
			}
		else			// v est Fermé ou Ouvert

			if ( nouveauCout < c(v))
				{
				if (etat(v) == OUVERT)
					PElement< Sommet>::retire(v,Ouverts);

				miseAJourVoisin( v, s, nouveauCout, Ouverts);

				}				// if (nouveauCout < v->c)
		}			// for

	PElement< pair<Sommet*,double> >::efface2(listeDesVoisins);
	}	// while (Ouverts)

return NULL; // échec

}	// aStar



static void miseAJourVoisin(Sommet * v, Sommet * s, const double & nouveauCout, PElement<Sommet> * & Ouverts)
{
pere(v) = s;
c(v) = nouveauCout;
g(v) = c(v) + h(v);
PElement<Sommet>::insertionOrdonnee( v, Ouverts, estPlusPetitOuEgal); etat(v) = OUVERT;
}




}; // AStarT

/**
Tâche : Construit sous une forme plus pratique le résultat de l'algo A* :
transforme sous forme de liste chaînée PElement<Sommet> la liste chaînée définie par les liens père qui a été produite par A*.

Rappel : L'algo A* crée une liste chaînée dont le maillon de tête est cible et dont le maillon final est départ.
La méthode chemin(,) construit une liste chaînée qui inverse le sens de parcours de la liste "lien père" produite par A*.
DONNEES :
cible : sommet final trouvé par A* (celui qui vérifie la condition estFinal(...))

RESULTATS : debut : qui pointe sur le 1er maillon de la nouvelle liste créée (il pointe donc aussi sur le sommet depart de l'algo A*)
et par return un pointeur sur le dernier maillon de la liste chaînée PElement<Sommet> * construite.
Le pointeur renvoyé par return pointe donc sur cible.

HYPOTHESE :
*/
template <class Sommet>
PElement<Sommet> * chemin( Sommet * cible, PElement<Sommet> * & debut)
{
if (!cible) 	// le chemin trouvé est vide (il n'y a donc pas de chemin)
   {
   debut = NULL; return NULL;
   }

else
	if (!pere(cible))		// le chemin trouvé contient un seul sommet. Cela signifie que départ = cible
	   {
	   debut = new PElement<Sommet>(cible,NULL);
	   return debut;
	   }
	else	// le chemin trouvé a au moins 2 sommets
	   {
	   PElement<Sommet> * d = chemin(pere(cible), debut);
	   d->s = new PElement<Sommet>(cible,NULL);
	   return d->s;
	   }
}

#endif



