#ifndef SOMMET_H
#define SOMMET_H

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "GElement.h"

using namespace std;

/**

Sommet d'un graphe en général

v est l'information associée au sommet : elle dépend de l'application du graphe
*/
template <class T>
class Sommet : public GElement<T>
{
public:
int degre;		// Rappel : degr?= nombre d'arêtes adjacentes ?ce sommet
/**

Un sommet est toujours créé isol?(c'est-?dire qu'il n'y a pas d'arête adjacente ?ce sommet)
*/
Sommet(const int clef, const T & v):GElement<T>(clef,v),degre(0){}

operator string () const;

};

template <class T>
Sommet<T>::operator string () const
{
ostringstream oss;

oss <<"Sommet("<<endl;
oss << GElement<T>::operator string()<<endl;
oss<<"degr?= " << degre << endl;
oss<<")";
return oss.str();
}

template <class T>
ostream & operator << (ostream & os, const Sommet<T> & sommet)
{
return os << (string)sommet;
}

#endif