#include <iostream>
#include <utility>

template <class S, class T>
ostream & operator << (ostream & os, const pair<S*,T*> & paire)
{
return os << "(" << *(paire.first) <<", " << *(paire.second) << ")";
}