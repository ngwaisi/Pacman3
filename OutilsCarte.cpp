#include <iostream>
//#include <fstream>

#include "InfosGrapheDessin.h"
#include "InfoAStar.h"
#include "InfoSommet.h"
#include "Sommet.h"
#include"InfoArete.h"
#include "Arete.h"

#include "Graphe.h"
#include "AStarT.h"
#include "Outils.h"
#include "OutilsCarte.h"
//#include "FenetreGrapheSFML.h"
//#include"FenetreGrapheSFMLAStar.h"
#include "SFML/Window/Event.hpp"
#include <stdlib.h>
#include <SFML/Graphics/Font.hpp>

#include <string>
#include "Vecteur2D.h"
#include "PElement.h"

#include<math.h>
using namespace std;
using namespace sf;

/*static*/ double OutilsCarte::distance( const Sommet<InfoSommet> * s1, const Sommet<InfoSommet> * s2)
{
return norme(s1->v.vSommet.p - s2->v.vSommet.p);
//return 0;
}

/*static*/ Arete<InfoArete, InfoSommet> *  OutilsCarte::creeArete(Sommet<InfoSommet> * sA, Sommet<InfoSommet> * sB, Graphe<InfoArete, InfoSommet> & graphe)
{
return graphe.creeArete( InfoArete( OutilsCarte::distance(sA,sB) ), sA, sB);
}

/*static*/ void OutilsCarte::libereToutSommet(Graphe<InfoArete, InfoSommet> & graphe)
{
PElement < Sommet<InfoSommet> > * l;


for (  l = graphe.lSommets; l ; l = l->s)
	{
	etat(l->v) = LIBRE;
	pere(l->v) = NULL;
	}
}


/*static*/ double OutilsCarte::hh(const Sommet<InfoSommet> * s)
{
return OutilsCarte::distance(s,OutilsCarte::cible);
}

/*static*/ PElement< pair<Sommet<InfoSommet>*,double> > * OutilsCarte::listeVoisins(const Sommet<InfoSommet> * s, const Graphe<InfoArete, InfoSommet> & graphe)
{
PElement< pair < Sommet<InfoSommet> *, Arete<InfoArete,InfoSommet> * > > * ladj, *lA;						// pair < Sommet<InfoSommet> *, Arete<InfoArete,InfoSommet> * >

ladj = graphe.adjacences(s);

PElement< pair<Sommet<InfoSommet>*,double> > * lVC;

for ( lA = ladj, lVC = NULL; lA; lA = lA->s)
	lVC = new PElement< pair<Sommet<InfoSommet>*,double> >( new pair<Sommet<InfoSommet>*,double>(lA->v->first,lA->v->second->v.cout1),lVC);


PElement< pair< Sommet<InfoSommet> *, Arete<InfoArete,InfoSommet> * > >::efface2(ladj);
return lVC;

}

/*static*/ Sommet<InfoSommet> *  OutilsCarte::pere( const Sommet<InfoSommet> * sommet)
{
return (Sommet<InfoSommet>*)sommet->v.infoAStar.pere;
}


/*static*/ Sommet<InfoSommet> * & OutilsCarte::pere( Sommet<InfoSommet> * sommet)
{
return (Sommet<InfoSommet> *&)(sommet->v.infoAStar.pere);
}

/*static*/ int & OutilsCarte::etat( Sommet<InfoSommet> * sommet)
{
return sommet->v.infoAStar.etat;
}

/*static*/ double & OutilsCarte::c( Sommet<InfoSommet> * sommet)
{
return sommet->v.infoAStar.c;
}

/*static*/ double & OutilsCarte::h( Sommet<InfoSommet> * sommet)
{
return sommet->v.infoAStar.h;
}

/*static*/ double OutilsCarte::g( const Sommet<InfoSommet> * sommet)
{
return sommet->v.infoAStar.g;
}


/*static*/ double & OutilsCarte::g( Sommet<InfoSommet> * sommet)
{
return sommet->v.infoAStar.g;
}

/*static*/ bool OutilsCarte::estFinal(const Sommet<InfoSommet> * sommet)
{
return sommet == cible;
}

/*static*/ Sommet<InfoSommet> * OutilsCarte::cible = NULL;


//--------------------- et maintenant les méthodes ordinaires appelées par A* -------------------------------------



void libereToutSommet(Graphe<InfoArete, InfoSommet> & graphe)
{
return OutilsCarte::libereToutSommet(graphe);
}

PElement< pair<Sommet<InfoSommet>*,double> > * listeVoisins(const Sommet<InfoSommet> * s, const Graphe<InfoArete, InfoSommet> & graphe)
{
return OutilsCarte::listeVoisins(s,graphe);
}

Sommet<InfoSommet> *  pere( const Sommet<InfoSommet> * sommet)
{
return OutilsCarte::pere(sommet);
}

Sommet<InfoSommet> * & pere( Sommet<InfoSommet> * sommet)
{
return OutilsCarte::pere(sommet);
}

int & etat( Sommet<InfoSommet> * sommet)
{
return OutilsCarte::etat(sommet);
}

double & c( Sommet<InfoSommet> * sommet)
{
return OutilsCarte::c(sommet);
}

double & h( Sommet<InfoSommet> * sommet)
{
return OutilsCarte::h(sommet);
}

double g( const Sommet<InfoSommet> * sommet)
{
return OutilsCarte::g(sommet);
}

double & g( Sommet<InfoSommet> * sommet)
{
return OutilsCarte::g(sommet);
}


/**
compte le nombre de maillons de la liste chaînée "pere" dont le maillon de tête est "tête".
*/
int longueurChemin(const Sommet<InfoSommet>* tete)
{
if (!tete)
	return 0;
else
	return 1 + longueurChemin(pere(tete));
}


const Sommet<InfoSommet> * dernierMaillon(const Sommet<InfoSommet>* tete)
{
if (!tete) return NULL;
else
	if (pere(tete) == NULL)
		return tete;
	else
		return dernierMaillon(pere(tete));

}


bool estFinal(const Sommet<InfoSommet> * sommet)
{
return OutilsCarte::estFinal(sommet);
}
