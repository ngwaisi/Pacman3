#ifndef SOMMET_H
#define SOMMET_H

#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include "GElement.h"

using namespace std;

/**

Sommet d'un graphe en g�n�ral

v est l'information associ�e au sommet : elle d�pend de l'application du graphe
*/
template <class T>
class Sommet : public GElement<T>
{
public:
int degre;		// Rappel : degr?= nombre d'ar�tes adjacentes ?ce sommet
/**

Un sommet est toujours cr�� isol?(c'est-?dire qu'il n'y a pas d'ar�te adjacente ?ce sommet)
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