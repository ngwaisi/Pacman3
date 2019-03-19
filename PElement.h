#ifndef PELEMENT_H
#define PELEMENT_H

#pragma once

/*
 * Pelement.h
 *
 * liste récursive dont les valeurs sont des pointeurs
 *
 * Attention : les méthodes récursives qui parcourent les listes doivent systématiquement être statiques !!!
 *
 *  Created on: 2 août 2012
 *      Author: Dominique
 */



#include <iostream>
#include <sstream>
#include <string>
#include "Erreur.h"
//#include <Reels.h>
//#include <Entiers.h>

using namespace std;

template <class T>
class PElement
{
public :
T * v;				// valeur
PElement<T> * s;	// suivant

/**
 *
 * Ne crée pas de copie de *v. Pointe donc sur la donnée originale *v
 *
 * */
PElement( T * v, PElement<T> * s ):v(v),s(s){}


// static void ecrit(ostream & os, const PElement<T> * p); // obsolète

/**
 * suppose que T est munie de la fct :   const String T::ecrit() const
 * Cette méthode est appelée pour chaque élément de p. Ainsi, si elle est virtuelle, p peut être hétérogène
 *
 * */
//static const string ecrit(const PElement<T> * p, const char * debut = "(", const char * separateur = ", ", const char * fin = ")");

//static const string toString(const PElement<T> * p, const string (*f)(const T &), const char * debut, const char * separateur, const char * fin);

static const string toString(const PElement<T> * p,  const char * debut="( ", const char * separateur = ", ", const char * fin=")");

static int taille(const PElement<T> * l);

/**
 *
 * ne recopie pas les données *v. réalise donc une copie partageant les données v avec l
 *
 * */
static  PElement<T> * copie1( PElement<T> * l);

/**
 *
 * recopie  toutes les données *v. réalise donc une copie ne partageant aucune donnée  avec l
 *
 * */
static  PElement<T> * copie2(const PElement<T> * l);

/**
 *
 * recopie  toutes les données *v à l'aide de la méthode v->copie(). réalise donc une copie ne partageant aucune donnée  avec l
 *
 * Alors si la classe T possède la méthode virtuelle copie(), l peut être hétérogène.
 * Et la méthode copie3 produit une copie de cette liste hétérogène.
 *
 * */

static PElement<T> * copie3(const PElement<T> * l);

/**
 * concatène l2 à la fin de l1. Ne crée aucun maillon.
 *
 * En sortie l1 pointe sur le début de la concaténation
 *
 * DONNEES : l1, l2 (peuvent être vides toutes les deux)
 *
 * RESULTATS : l1 contenant la concaténation
 *
 * Exemple 1 : si en entrée l1 = (2,5,4) et l2 = (7,11) alors en sortie l1 = (2,5,4,7,11) et l2 = (7,11)
 * Exemple 2 : si en entrée l1 = () et l2 = (7,11) alors en sortie l1 = (7,11) et  l2 = (7,11)
 * Exemple 3 : si en entrée l1 = (9,5) et l2 = () alors en sortie l1 = (9,5) et l2 = ()
 *
 * */
static void concat(PElement<T> * & l1, PElement<T> *  l2);

/**
 * efface toute la liste l
 * mais n'efface pas les données *v
 *
 * */
static void efface1(PElement<T>* & l);

/**
 * efface toute la liste l
 * et efface toutes les données *v
 *
 * */
static void efface2(PElement<T>* & l);

/**
 * recherche si a appartient à l
 *
 * renvoie un pointeur sur le maillon de l contenant a
 * renvoie NULL si a n'appartient pas à l
 *
 * */
static  PElement< T > * appartient( const T * a,  PElement<T> * l);

/**
 * HYPOTHESES : l'évaluation de condition() produit un booléen
 * condition est supposée avoir la signature : bool condition( const T * a)
 *
 * renvoie un pointeur sur le 1er maillon de l vérifiant la condition "condition"
 * renvoie NULL si aucun maillon ne vérifie la condition
 *
 * */
template <class FONCTEUR>
static PElement< T > * appartient(  PElement<T> * l, const FONCTEUR & condition);
/**
 * Insère * a dans l de telle sorte que l reste ordonnée par ordre croissant (l'élement en tête est le plus petit).
 * Ne réalise pas de copie de *a. En sortie l et a partagent donc physiquement des données.
 *
 * A l'instar de la méthode précédente (appartient), cette fonction aurait aussi pu être écrite avec un argument foncteur
 *
 * Données : a (l'élément à insérer), l, estPlusPetitOuEgal(la fonction de comparaison))
 * Résultats : l modifiée par l'insertion
 * Hypothèses : on suppose l ordonnée par ordre croissant à l'appel
 *
 * */
static void insertionOrdonnee( T * a, PElement<T> * & l, bool (*estPlusPetitOuEgal)(const T * a1, const T * a2));

/**
 * retire la 1ère occurrence de a de l si a est présent dans l, sinon ne fait rien
 *
 * L'élément trouvé n'est pas effacé
 *
 * La comparaison est faite sur les pointeurs
 *
 * Données : a, l
 * Résultats : l (éventuellement modifiée), par return : true si l'élément a été trouvé, false sinon
 * */
static bool retire(const T * a, PElement<T> * & l);


/**
 * retire l'élément situé en tête de l et le renvoie. Le 1er maillon de l est effacé.
 *
 * l est donc modifiée par l'appel. En sortie l compte un élément de moins.
 * lance une exception Erreur si l == NULL à l'appel
 *
 * */
static T * depiler(PElement<T> * & l);

//-------------------------- PElement<T> ------------------------------
};

template<class T>
ostream& operator <<(ostream & os, const PElement<T> * p){ return os << PElement<T>::toString(p);}


/**
 * suppose que T est munie de la fct :   const String T::ecrit() const
 * Cette méthode est appelée pour chaque élément de p. Ainsi, si elle est virtuelle, p peut être hétérogène
 *
 * */
//template <class T>
///*static*/ const string PElement<T>::ecrit( const PElement<T> * p, const char * debut, const char * separateur, const char * fin)
//{
//string s;
//for ( s = debut; p ; p = p->s)
//    s += p->v->ecrit()+separateur;
//
//return s+fin;
//}



template <class T>
/*static*/ const string PElement<T>::toString(const PElement<T> * p,  const char * debut, const char * separateur, const char * fin)
{
PElement<T> * r;
ostringstream oss;

for ( r = (PElement<T>* ) p, oss << debut; r; r = r->s)
    oss << *(r->v) << separateur;

oss << fin;
return oss.str();
}

template <class T>
/* static */ void PElement<T>::concat(PElement<T> * & l1, PElement<T> * l2)
{
if (!l1)        /* l1 == liste vide */
  l1 = l2;

else
  concat(l1->s, l2);
}

template <class T>
/* static */ int PElement<T>::taille(const PElement<T> * l)
{
if (!l) return 0;
else
  return 1 + PElement<T>::taille(l->s);
}


/**
 *
 * ne recopie pas les données *v. réalise donc une copie partageant les données v avec l
 *
 * */
template <class T>
/* static */ PElement<T> * PElement<T>::copie1( PElement<T> * l)
{
if (!l)
   return NULL;
else
   return new PElement<T>(l->v, PElement<T>::copie1(l->s));
}

/**
 *
 * recopie  toutes les données *v. réalise donc une copie ne partageant aucune donnée  avec l
 *
 * */
template <class T>
/* static */ PElement<T> * PElement<T>::copie2(const PElement<T> * l)
{
if (!l)
   return NULL;
else
   return new PElement<T>(new T(*(l->v)), PElement<T>::copie2(l->s));
}

/**
 *
 * recopie  toutes les données *v à l'aide de la méthode v->copie(). réalise donc une copie ne partageant aucune donnée  avec l
 *
 * Alors si la classe T possède la méthode virtuelle copie(), l peut être hétérogène. Et la méthode copie3 produit une copie de cette liste hétérogène.
 *
 * */
template <class T>
/* static */ PElement<T> * PElement<T>::copie3(const PElement<T> * l)
{
if (!l)
   return NULL;
else
   return new PElement<T>( l->v->copie(), PElement<T>::copie3(l->s));
}



/**
 * efface toute la liste l
 * mais n'efface pas les données *v
 *
 * */
template <class T>
/* static */ void PElement<T>::efface1(PElement<T>* & l)
{
if (l)
   {
   PElement<T>::efface1(l->s);
   delete l; l = NULL;
   }
}
/**
 * efface toute la liste l
 * et efface toutes les données *v
 *
 * */
template <class T>
/* static */ void PElement<T>::efface2(PElement<T>* & l)
{
if (l)
   {
   PElement<T>::efface2(l->s);
   delete l->v; delete l; l = NULL;
   }
}
/**
 * recherche si a appartient à l
 *
 * renvoie un pointeur sur le maillon de l contenant a
 * renvoie NULL si a n'appartient pas à l
 *
 * */
template <class T>
PElement< T > * PElement< T >::appartient( const T * a, PElement<T> * l)
{
for ( ; l; l = l->s)
    if (a == l->v)
       return l;

return l;
}

/**
 * HYPOTHESES : l'évaluation de condition() produit un booléen
 * condition est supposée avoir la signature : bool condition( const T * a)
 *
 * renvoie un pointeur sur le 1er maillon de l vérifiant la condition "condition"
 * renvoie NULL si aucun maillon ne vérifie la condition
 *
 * */
template <class T>
template <class FONCTEUR>
/*static*/ PElement< T > * PElement< T >::appartient(  PElement<T> * l, const FONCTEUR & condition)
{
for ( ; l; l = l->s)
    if (condition(l->v))
       return l;

return l;
}

/**
 * Insère * a dans l de telle sorte que l reste ordonnée par ordre croissant (l'élement en tête est le plus petit).
 * Ne réalise pas de copie de *a. En sortie l et a partagent donc physiquement des données.
 *
 * A l'instar de la méthode précédente (appartient), cette fonction aurait aussi pu être écrite avec un argument foncteur
 *
 * Données : a (l'élément à insérer), l, estPlusPetitOuEgal(la fonction de comparaison))
 * Résultats : l modifiée par l'insertion
 * Hypothèses : on suppose l ordonnée par ordre croissant à l'appel
 *
 * */
template<class T>
/*static*/ void PElement<T>::insertionOrdonnee( T * a, PElement<T> * & l, bool (*estPlusPetitOuEgal)(const T * a1, const T * a2))
{
if (!l || estPlusPetitOuEgal(a,l->v))
   l = new PElement<T>(a,l);
else
   PElement<T>::insertionOrdonnee(a,l->s,estPlusPetitOuEgal);
}

/**
 * retire la 1ère occurrence de a de l si a est présent dans l, sinon ne fait rien
 *
 * L'élément trouvé n'est pas effacé
 *
 * La comparaison est faite sur les pointeurs
 *
 * Données : a, l
 * Résultats : l (éventuellement modifiée), par return : true si l'élément a été trouvé, false sinon
 * */
template<class T>
/*static*/ bool PElement<T>::retire(const T * a, PElement<T> * & l)
{
if (!l)
   return false;
else
   if (a == l->v)
      {
      PElement<T> * r = l; l = l->s; delete r;
      return true;
      }
   else
      return PElement<T>::retire(a,l->s);
}

/**
 * retire l'élément situé en tête de l et le renvoie. Le 1er maillon de l est effacé.
 *
 * l est donc modifiée par l'appel. En sortie l compte un élément de moins.
 * lance une exception Erreur si l == NULL à l'appel
 *
 * */
template <class T>
/* static */ T * PElement<T>::depiler(PElement<T> * & l)
{
if (!l) throw Erreur("impossible de dépiler une pile vide");
T * a = l->v;
PElement<T> * tete = l;

l = l->s; delete tete;
return a;

}





/**
 *
 * ne recopie pas les données *v. réalise donc la réunion au sens ensembliste de l1 et l2  partageant les données v avec l1 et l2.
 *
 * Suppose que l1 et l2 sont des ensembles. Elles ne contiennent donc aucun doublon.
 *
 * DONNEES : l1 et l2 (représentant des ensembles)
 * RESULTAT : l1 U l2 au sens ensembliste partageant les données v avec l1 er l2
 *
 * */
template <class T>
PElement<T> * reunion( PElement<T> * l1,  PElement<T> * l2)
{
PElement<T> * r = PElement<T>::copie1(l2);
PElement<T> * pl1;

for ( pl1 = l1; pl1; pl1 = pl1->s)
    if (!PElement<T>::appartient(pl1->v,r))
       r = new PElement<T>(pl1->v,r);

return r;
}



/**
 * partage p en deux listes p et p1 de taille égale : Laisse dans p les éléments de rang impair et place dans p1 les éléments de rang pair
 *
 * DONNEES : p
 * RESULTATS : p (modifiée) et p1
 *
 * */
template <class T>
void partage(PElement<T> * & p, PElement<T> * & p1)
{
if (p == NULL || p->s == NULL)
   p1 = NULL;
else
   {
   PElement<T> *  r1, *r2;

   r1 = p->s;
   r2 = r1->s;

   partage(r2,p1);

   r1->s = p1;
   p->s = r2;
   p1 = r1;
   }
}

/**
 * réalise la fusion ordonnée de p1 et p2 et place le résultat dans p1. En sortie p2 est donc vide.
 * Ne crée aucun maillon.
 *
 * Suppose que p1 et p2 sont ordonnées par ordre croissant en entrée. La liste résultante est aussi ordonnée par ordre croissant.
 *
 * Utilise la fct estPlusPetitOuEgal pour les comparaisons 1 à 1.
 *
 * On suppose que estPlusPetitOuEgal(a1,a2) renvoie true si a1 <= a2 où <= est une relation d'ordre sur T et renvoie false si a1 > a2
 *
 * DONNEES : p1 et p2
 * RESULTATS: P1 et p2
 *
 * */
template <class T>
void fusion(PElement<T> * & p1, PElement<T> * & p2, bool (*estPlusPetitOuEgal)(const T * a1, const T * a2))
{
if (!p2) return; // p2 est vide, il n'y a rien à faire

if (!p1) // p1 est vide et p2 ne l'est pas
   {
   p1 = p2; p2 =  NULL;
   return;
   }

// à présent, p1 et p2 sont non vides

if (estPlusPetitOuEgal(p1->v,p2->v)) // p1->v <= p2->v
   {
   PElement<T> * r;
   r = p1->s;
   fusion(r,p2,estPlusPetitOuEgal);
   p1->s = r;
   }
else // p1->v > p2->v
   {
   PElement<T> * r;
   r = p2->s;
   fusion(p1,r,estPlusPetitOuEgal);
   p2->s = p1;
   p1 = p2;
   p2 = NULL;
   }
}


/**
 * trie p par tri récursif dichotomique (trifusion)
 *
 * ne crée pas de nouveau maillon. La liste originale p est modifiée
 *
 * Utilise la fct estPlusPetitOuEgal pour les comparaisons 1 à 1.
 *
 * range les éléments par ordre croissant
 *
 * On suppose que estPlusPetitOuEgal(a1,a2) renvoie true si a1 <= a2 où <= est une relation d'ordre sur T et renvoie false si a1 > a2
 *
 * DONNEES : p
 * RESULTATS : p modifiée
 *
 * */
template <class T>
void tri(PElement<T>* & p, bool (*estPlusPetitOuEgal)( const T * a1, const T * a2))
{
if (p != NULL && p->s != NULL)
   {
   PElement<T> * p1;

   partage(p,p1);

   tri(p,estPlusPetitOuEgal); tri(p1,estPlusPetitOuEgal);

   fusion(p,p1,estPlusPetitOuEgal);
   }
}

#endif


