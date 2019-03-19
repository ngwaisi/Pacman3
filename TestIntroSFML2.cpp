
#include <iostream>
#include<SFML/Graphics/RenderWindow.hpp>
#include<SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

using namespace sf;
using namespace std;
int main()
{
cout <<"intro SFML2. pareil que intro SFML mais avec un makefile et des librairies statiques" << endl;

sf::RenderWindow maFenetre(sf::VideoMode(500,300),"ma 1ère fenêtre (avec makefile)");

//maFenetre.clear(sf::Color::Black);
sf::VertexArray truc(sf::PrimitiveType::LineStrip);
Vector2f pA(30.0,20.0);
Vector2f pB(110.0,100.0);
Color couleurA = Color::Yellow;
Color couleurB = Color::Red;
Vertex A(pA,couleurA);
Vertex B(pB,couleurB);
truc.append(A);
truc.append(B);
maFenetre.draw(truc);
maFenetre.display();


while( maFenetre.isOpen())
	 {
	 Event event;
	 while(maFenetre.pollEvent(event))
		  {
		  if (event.type == Event/*::EventType*/::MouseButtonPressed)
		     {
			 Mouse::Button bouton = event.mouseButton.button;
			 int x = event.mouseButton.x;
			 int y = event.mouseButton.y;
		     cout <<"coordonnées souris : x = " << x <<", y = " << y << endl;
			 if (bouton == Mouse::Button::Left) cout <<"bouton gauche enfoncé" << endl;
			 }
		  if (event.type == Event::EventType::KeyPressed)
			 {
			 Event::KeyEvent touche = event.key;
			 Keyboard::Key code = touche.code;
			 bool shiftEstAppuye = touche.shift;

			 if (shiftEstAppuye) cout <<"touche shift enfoncée" << endl;
			 if (code == Keyboard::Key::Num5) cout <<"touche 5 principale enfoncée" << endl;
			 if (code == Keyboard::Key::Numpad5) cout <<"touche 5 pavé numérique enfoncée" << endl;

			 cout <<"touche enfoncée = " << (int) code <<", " << (char) code << endl;
		     }
		  if (event.type == Event::EventType::Closed)
			 maFenetre.close();
		  }

	 }
char ch; cin >> ch;
return 0;
}
