/**
Test des fonctionnalit�s de PElement : la classe template repr�sentant des listes lin�aires r�cursives


*/
#include <iostream>
#include <string>
#include <stdlib.h>
#include "PElement.h"

using namespace std;


bool plusPetitOuEgal(const double * x, const double * y)
{
return *x <= *y;
}

bool plusPetitOuEgal(const string * x, const string * y)
{
return x->compare( *y) <= 0;
}

/*
cr��e pour tester la m�thode

template <class FONCTEUR>
static PElement< T > * appartient(  PElement<T> * l, const FONCTEUR & condition);

avec T == double

*/
class ConditionPlusGrandQue
{
public :
double x;
ConditionPlusGrandQue(const double & x) : x(x) {}
bool operator () (const double * a) const { return *a > x;}
};

/*
cr��e aussi pour tester la m�thode

template <class FONCTEUR>
static PElement< T > * appartient(  PElement<T> * l, const FONCTEUR & condition);

avec T == double

*/
bool plusGrandQue5 (const double * a) {return *a > 5;}

int main()
{
char ch;

cout << "test des fonctionnalit�s de la classe PElement<T> pour 2 cas : T == double et avec T == string "<< endl;

cout <<"test du constructeur ?" << endl; cin >> ch;

double x1(2), x2(5), x3(7.5), x4(9);
string s1 = "carotte", s2 = "cerise", s3 = "orange";
PElement<double> * l1;
PElement<string> * l2;

l1 = NULL;
l1 = new PElement<double>(&x4,l1);
l1 = new PElement<double>(&x3,l1);
l1 = new PElement<double>(&x2,l1);
l1 = new PElement<double>(&x1,l1);

l2 = new PElement<string>(&s1,new PElement<string>(&s2,new PElement<string>(&s3,NULL)));

cout << "l1 = " << l1 << endl;
cout << "l2 = " << l2 << endl;

cout <<"test de la m�thode taille() ? " << endl; cin >> ch;
int n1, n2;
n1 = PElement<double>::taille(l1); n2 = PElement<string>::taille(l2);

cout << "taille de l1  = " << n1 << ", taille de l2 = " << n2 << endl;

cout <<"test de la m�thode insertionOrdonnee()  ?" << endl; cin >> ch;


double y1(-7),y2(6),y3(13);
string c1("fraise"),c2("ananas"),c3("pomme");

PElement<double>::insertionOrdonnee(&y1,l1,plusPetitOuEgal);
PElement<double>::insertionOrdonnee(&y2,l1,plusPetitOuEgal);
PElement<double>::insertionOrdonnee(&y3,l1,plusPetitOuEgal);

PElement<string>::insertionOrdonnee(&c1,l2,plusPetitOuEgal);
PElement<string>::insertionOrdonnee(&c2,l2,plusPetitOuEgal);
PElement<string>::insertionOrdonnee(&c3,l2,plusPetitOuEgal);

cout << "apr�s insertion ordonn�e des 3 valeurs "<< y1 <<", "<< y2 << " et "<< y3 << ", "<< endl << "l1 = " << l1 << endl;
cout << "apr�s insertion ordonn�e de 3 valeurs, "<< c1 <<", "<< c2 << " et "<< c3 <<", "<< endl << "l2 = " << l2 << endl;

cout <<"test de la m�thode d�piler() ? " << endl; cin >> ch;

double * p1 = PElement<double>::depiler(l1);

cout << "l1 a �t?d�pil�e, l1 = " << l1 << endl;
cout << "la valeur extraite est : " << *p1 << endl;

string * p2 = PElement<string>::depiler(l2);

cout << "l2 a �t?d�pil�e, l2 = " << l2 << endl;
cout << "la valeur extraite est : " << *p2 << endl;

cout <<"test de la m�thode retire()  ? " << endl; cin >> ch;

bool ok1 = PElement<double>::retire(&y2,l1);

bool ok2 = PElement<string>::retire(&s1,l2);

if (ok1) cout << y2 << " a �t?retir�e de l1, ?pr�sent l1 = " << l1 << endl;

if (ok2) cout << s1 << " a �t?retir�e de l2, ?pr�sent l2 = " << l2 << endl;

cout <<"test de la m�thode efface1() ?" << endl; cin >> ch;

PElement<double>::efface1(l1);

cout << "l1 a �t?effac�e avec efface1(), ?pr�sent l1 = " << l1 << endl;

PElement<string>::efface1(l2);

cout << "l2 a �t?effac�e avec efface1(), ?pr�sent l2 = " << l2 << endl;

cout <<"test de la m�thode efface2()  ?" << endl; cin >> ch;

l1 = new PElement<double>( new double(2),new PElement<double>(new double(7),new PElement<double>(new double(13),NULL)));

cout << " l1 a �t?re-cr��e avec des valeurs allou�es dynamiquement,"<< endl << " l1 = "<<l1 << endl;

l2 = new PElement<string>(new string("rene"),new PElement<string>(new string("la"),new PElement<string>(new string("taupe"),NULL)));

cout << " l2 a �t?re-cr��e avec des valeurs allou�es dynamiquement,"<< endl << " l2 = "<<l2 << endl;

PElement<double>::efface2(l1);

cout << "l1 a �t?effac�e avec efface2(), ?pr�sent l1 = " << l1 << endl;

PElement<string>::efface2(l2);

cout << "l2 a �t?effac�e avec efface2(), ?pr�sent l2 = " << l2 << endl;

{
cout <<"test de la m�thode static const PElement< T > * appartient( const T * a, const PElement<T> * l); ? " << endl; cin >> ch;

double x1(2), x2(5), x3(7.5), x4(9);
string s1 = "carotte", s2 = "cerise", s3 = "orange";
PElement<double> * l1;
PElement<string> * l2;

l1 = NULL;
l1 = new PElement<double>(&x4,l1);
l1 = new PElement<double>(&x3,l1);
l1 = new PElement<double>(&x2,l1);
l1 = new PElement<double>(&x1,l1);

l2 = new PElement<string>(&s1,new PElement<string>(&s2,new PElement<string>(&s3,NULL)));

cout << "l1 = " << l1 << endl;
cout << "l2 = " << l2 << endl;
cout <<"on cherche le pointeur sur " << x3 <<" dans l1" << endl;
PElement<double> * p = PElement<double>::appartient(&x3,l1);
cout <<" p = " << p << endl;
double a = 11;
cout <<"on cherche le pointeur sur " << a <<" dans l1" << endl;
p = PElement<double>::appartient(&a,l1);
cout <<" p = " << p << endl;
}

{
cout <<"test de la m�thode template <class FONCTEUR>" << endl;
cout <<" static PElement< T > * appartient(  PElement<T> * l, const FONCTEUR & condition); ? " << endl; cin >> ch;

double x1(2), x2(5), x3(7.5), x4(9);
string s1 = "carotte", s2 = "cerise", s3 = "orange";
PElement<double> * l1;
PElement<string> * l2;

l1 = NULL;
l1 = new PElement<double>(&x4,l1);
l1 = new PElement<double>(&x3,l1);
l1 = new PElement<double>(&x2,l1);
l1 = new PElement<double>(&x1,l1);

cout << "l1 = " << l1 << endl;


ConditionPlusGrandQue condition( 6);
cout <<"on cherche le 1er �l�ment de l1 qui soit > 6" << endl;
PElement< double > * p = PElement<double>::appartient(  l1, condition);
cout <<" p = " << p << endl;
cout <<"on cherche le 1er �l�ment de l1 qui soit > 5" << endl;
p = PElement<double>::appartient<bool (*) (const double *)>(  l1, plusGrandQue5);
cout <<" p = " << p << endl;
cin >> ch;
}
return 0;
}
