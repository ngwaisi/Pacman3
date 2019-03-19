#ifndef FENETREGRAPHESFML_H
#define FENETREGRAPHESFML_H

#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/VertexArray.hpp>
//#include <SFML/Graphics/Vertex.hpp>
#include<SFML/GRAPHICS/CircleShape.hpp>
#include<SFML/GRAPHICS/ConvexShape.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Sommet.h"
#include"Arete.h"
#include"InfosGrapheDessin.h"
//#include <InfoSommet.h>
//#include <InfoArete.h>
#include "TransfoAffine2D.h"
#include "Vecteur2D.h"
using namespace sf;
using namespace std;

/**
Prend en charge le dessin d'un graphe.
Suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re Monde.
Prend en charge le passage fen�tre-cl�ture
*/


inline const Vector2f vecteur2DToVector2f( const Vecteur2D & v) { float x,y; v.arrondit(x,y); return Vector2f(x,y);}


/**

vSommet : en coordonn�es monde
*/
inline bool dessinePetitRond(RenderWindow & fenetre, const TransfoAffine2D & t, const VSommet & vSommet, const Font & font,
							const Vecteur2D & deltaTextePixels = Vecteur2D(VSommet::rayonDisquePixels, VSommet::rayonDisquePixels))
{
Vecteur2D position = t.applique(vSommet.p);
Vecteur2D position1 = position -VSommet::rayonDisquePixels*Vecteur2D(1,1);

// si on appliquait la transfo t globalement ?tout le graphe avant de commencer ?dessiner, on optimiserait
// bcp de calculs !!!!

CircleShape disque((float)VSommet::rayonDisquePixels);
disque.setFillColor(Color(vSommet.couleur));
float epaisseurBord = (float)(0.15*VSommet::rayonDisquePixels);
disque.setOutlineThickness(epaisseurBord);
disque.setOutlineColor(Color(VSommet::couleurBord));

Vector2f p1 = vecteur2DToVector2f(position1);

disque.setPosition(p1);

fenetre.draw(disque);

Vecteur2D position2 = position - deltaTextePixels;
unsigned int tailleEnPixels = 17;
Text texte(vSommet.nom, font,tailleEnPixels);
texte.setFillColor(Color::Black);
texte.setPosition(vecteur2DToVector2f(position2));
fenetre.draw(texte);
return true;
}

/**
d�but et fin sont en coordonn�es monde
*/
inline bool dessineSegment( RenderWindow & fenetre, const TransfoAffine2D & t, const unsigned int couleur,
						const Vecteur2D & debut, const Vecteur2D & fin, const unsigned int epaisseurTraitPixels = 2)
{
// on va dessiner un rectangle tr�s fin pour repr�senter l'ar�te

Vecteur2D A, B;	// {AB] est l'ar�te ?repr�senter

A = t.applique(debut); B = t.applique(fin);		// on passe des coordonn�es monde aux coordonn�es �cran

Vecteur2D u = B-A;

double nU = norme(u);
u /=nU;
Vecteur2D  n = u.rotationDirecteQuartDeTour();

//double e = 1;	// �paisseur du rectangle = 2*e. longueur du rectangle == AB
double e = 0.5*epaisseurTraitPixels;	// �paisseur du rectangle = 2*e. longueur du rectangle == AB


Vecteur2D v = e*n;

Vecteur2D A0= A-v,A1 = B-v, A2 = B+v,A3 = A+v; // on calcule les 4 sommets du rectangle dont l'ar�te [AB] est un axe de sym�trie

Vector2f F0 = vecteur2DToVector2f(A0);
Vector2f F1 = vecteur2DToVector2f(A1);
Vector2f F2 = vecteur2DToVector2f(A2);
Vector2f F3 = vecteur2DToVector2f(A3);

ConvexShape rectangle(4);
rectangle.setPoint(0,F0);
rectangle.setPoint(1,F1);
rectangle.setPoint(2,F2);
rectangle.setPoint(3,F3);

rectangle.setFillColor(Color(couleur));
fenetre.draw(rectangle);

return true;
}


/**
Prend en charge le dessin d'un graphe
Prend en charge le passage de coordonn�es monde ---> �cran
*/
class FenetreGrapheSFML
{
public:
RenderWindow fenetre;
const Font & font;


TransfoAffine2D t;	// r�alise le passage fen�tre-cl�ture (ou encore monde vers �cran)
/**
Cr�e la fen�tre qui va contenir le dessin du graphe.

DONNEES : titre : titre de la fen�tre
		  fondCarte : couleur du fond de la sc�ne au formar RGBA
          coinBG : coin Bas Gauche de la sc�ne en coordonn�es monde
          coinHD : coin Haut Droit de la sc�ne en coordonn�es monde
          largeur : largeur de la fen�tre �cran (en pixels)
          hauteur : hauteur de la fen�tre �cran (en pixels)
          font : police ?utiliser pour les annotations sur les sommets

*/
FenetreGrapheSFML( const string & titre, const unsigned int fondCarte,
				const Vecteur2D & coinBG, const Vecteur2D & coinHD,
								  const int largeur, const int hauteur, const Font & font):
								  	fenetre(sf::VideoMode(largeur,hauteur), titre), font(font)
{
fenetre.clear(Color(fondCarte));
// calcul de la transformation affine - changement de rep�re : monde ---> �cran
Vecteur2D coinEcranBG(0,hauteur), coinEcranHD(largeur,0);
t = TransfoAffine2D::passageMondeEcran(coinBG,coinHD,coinEcranBG,coinEcranHD);
}
/**
Dessine un sommet du graphe. Exemples :  nom, couleur, informations associ�es, etc.
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es du sommet sont d�finies par rapport au rep�re du monde
*/
template <class T>
bool dessine(const Sommet<T> * sommet) ;

/**
Dessine l'ar�te (d�but->fin) en utilisant la couleur "couleur"
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re du monde
*/
template <class T>
bool dessine(const Sommet<T> * debut, const Sommet<T> * fin, unsigned int couleur);

/**
Dessine un ar�te du graphe. Exemples :  nom, couleur, informations associ�es, etc.
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re du monde
*/
template <class S, class T>
bool dessine(const Arete<S,T> * arete) ;

};

template <>
bool FenetreGrapheSFML::dessine<VSommet>(const Sommet<VSommet> * sommet)
{
return dessinePetitRond(this->fenetre,this->t, sommet->v, this->font);	// m�thode ordinaire. cf. d�but de ce fichier
}

/*
{
Vecteur2D position = t.applique(sommet->v.p)-VSommet::rayonDisquePixels*Vecteur2D(1,1);

// si on appliquait la transfo t globalement ?tout le graphe avant de commencer ?dessiner, on optimiserait
// bcp de calculs !!!!

CircleShape disque((float)VSommet::rayonDisquePixels);
disque.setFillColor(Color(sommet->v.couleur));
float epaisseurBord = (float)(0.15*VSommet::rayonDisquePixels);
disque.setOutlineThickness(epaisseurBord);
disque.setOutlineColor(Color(VSommet::couleurBord));
float x,y;
position.arrondit(x,y);

disque.setPosition(x, y);

fenetre.draw(disque);

unsigned int tailleEnPixels = 15;
Text texte(sommet->v.nom, font,tailleEnPixels);
texte.setFillColor(Color::Black);
texte.setPosition(x,y);
fenetre.draw(texte);
return true;
}
*/

template <>
bool FenetreGrapheSFML::dessine<Peinture,VSommet>(const Arete<Peinture,VSommet> * arete)
{
	   dessineSegment( this->fenetre, this->t,   arete->v.fond, arete->debut->v.p, arete->fin->v.p);
return dessineSegment( this->fenetre, this->t, arete->v.devant, arete->debut->v.p, arete->fin->v.p);
}

/*{
// on va dessiner un rectangle tr�s fin pour repr�senter l'ar�te

Vecteur2D A(arete->debut->v.p), B(arete->fin->v.p);	// {AB] est l'ar�te ?repr�senter

A = t.applique(A); B = t.applique(B);		// on passe des coordonn�es monde aux coordonn�es �cran

Vecteur2D u = B-A;

double nU = norme(u);
u /=nU;
Vecteur2D  n = u.rotationDirecteQuartDeTour();

double e = 1;	// �paisseur du rectangle = 2*e. longueur du rectangle == AB

Vecteur2D v = e*n;

Vecteur2D A0= A-v,A1 = B-v, A2 = B+v,A3 = A+v; // on calcule les 4 sommets du rectangle dont l'ar�te [AB] est un axe de sym�trie

Vector2f F0 = vecteur2DToVector2f(A0);
Vector2f F1 = vecteur2DToVector2f(A1);
Vector2f F2 = vecteur2DToVector2f(A2);
Vector2f F3 = vecteur2DToVector2f(A3);

ConvexShape rectangle(4);
rectangle.setPoint(0,F0);
rectangle.setPoint(1,F1);
rectangle.setPoint(2,F2);
rectangle.setPoint(3,F3);

rectangle.setFillColor(Color(arete->v.fond));
fenetre.draw(rectangle);
rectangle.setFillColor(Color(arete->v.devant));
fenetre.draw(rectangle);

return true;
}*/

//---------------------------------------dessine le cas particulier de InfoSommet et InfoArete ------------------------------

/* *
Dessine un sommet du graphe. Exemples :  nom, couleur, informations associ�es, etc.
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es du sommet sont d�finies par rapport au rep�re du monde
* /
template <>
bool FenetreGrapheSFML::dessine<InfoSommet>(const Sommet<InfoSommet> * sommet)
{
return dessinePetitRond(this->fenetre, this->t, sommet->v.vSommet, this->font);
}

/ **
Dessine un ar�te du graphe. Exemples :  nom, couleur, informations associ�es, etc.
renvoie true en cas de succ�s, false en cas d'�chec
On suppose que les coordonn�es des sommets sont d�finies par rapport au rep�re du monde
* /
template <>
bool FenetreGrapheSFML::dessine<InfoArete,InfoSommet>(const Arete<InfoArete,InfoSommet> * arete)
{
return dessineSegment( this->fenetre, this->t, arete->v.couleur, arete->debut->v.vSommet.p, arete->fin->v.vSommet.p);
}
*/


//----------------------------------------------------------------------------------
/**
par rapport ?la classe de base, cette fen�tre dessine en plus les axes du rep�re monde

*/
class FenetreGrapheSFMLAvecAxesRepereMonde : public FenetreGrapheSFML
{
const Font & font2;

public:

/**
Cr�e la fen�tre qui va contenir le dessin du graphe.

DONNEES : titre : titre de la fen�tre
		  fondCarte : couleur du fond de la sc�ne au formar RGBA
          coinBG : coin Bas Gauche de la sc�ne en coordonn�es monde
          coinHD : coin Haut Droit de la sc�ne en coordonn�es monde
          largeur : largeur de la fen�tre �cran (en pixels)
          hauteur : hauteur de la fen�tre �cran (en pixels)
          font1 : police ?utiliser pour les annotations sur les sommets
		  font2 : police ?utiliser pour les annotations sur les axes du rep�re
*/

FenetreGrapheSFMLAvecAxesRepereMonde(const string & titre, unsigned int fondCarte,
								const Vecteur2D & coinBG, const Vecteur2D & coinHD,
								  const int largeur, const int hauteur, const Font & font1, const Font & font2):
							FenetreGrapheSFML( titre, fondCarte, coinBG, coinHD, largeur, hauteur, font1), font2(font2)
{
//------------ on va dessiner les axes du rep�re avec les annotations usuelles O, I et J -------------

//---------- d'abord on d�finit les points utiles

Vecteur2D O, I(1,0),J(0,1);
Vecteur2D A0(coinBG.x,0), A1(coinHD.x,0);	// restriction de l'axe des abscisses au rectangle monde
Vecteur2D B0(0,coinBG.y), B1(0,coinHD.y);	// restriction de l'axe des ordonn�es au rectangle monde

//---------------- on passe des coordonn�es monde ---> �cran

O = t.applique(O);
I = t.applique(I);
J = t.applique(J);

A0 = t.applique(A0);
A1 = t.applique(A1);

B0 = t.applique(B0);
B1 = t.applique(B1);

//-------------------- on dessine les 2 axes --------------------------------

VertexArray axeAbscisses(PrimitiveType::Lines);

axeAbscisses.append(Vertex(vecteur2DToVector2f(A0),Color::Black));
axeAbscisses.append(Vertex(vecteur2DToVector2f(A1),Color::Black));

fenetre.draw(axeAbscisses);

VertexArray axeOrdonnees(PrimitiveType::Lines);

axeOrdonnees.append(Vertex(vecteur2DToVector2f(B0),Color::Black));
axeOrdonnees.append(Vertex(vecteur2DToVector2f(B1),Color::Black));

fenetre.draw(axeOrdonnees);

//------------------------------ on dessine les points O, I et J

float rayonPointPixels = 4;
Vecteur2D u(1,1);

Vecteur2D ru = rayonPointPixels*u;

CircleShape O1(rayonPointPixels);
O1.setFillColor(Color::Red);
O1.setPosition(vecteur2DToVector2f(O-ru));
fenetre.draw(O1);
O1.setPosition(vecteur2DToVector2f(I-ru));
fenetre.draw(O1);
O1.setPosition(vecteur2DToVector2f(J-ru));
fenetre.draw(O1);

//----------------- on dessine les annotations -----------------------

unsigned int tailleEnPixels = 12;
Text annotation("O", font2,tailleEnPixels);
annotation.setFillColor(Color::Red);
double d = 2*rayonPointPixels;
Vecteur2D v(1,-1);
annotation.setPosition(vecteur2DToVector2f(O+d*v));
fenetre.draw(annotation);

annotation.setString("I");
annotation.setPosition(vecteur2DToVector2f(I+d*v));
fenetre.draw(annotation);

annotation.setString("J");
annotation.setPosition(vecteur2DToVector2f(J+d*v));
fenetre.draw(annotation);

// on  pourrait optimiser les lignes de calcul ci-dessus pour �viter quelques r�p�titions ----------------

}

};


#endif // FENETRE_H
