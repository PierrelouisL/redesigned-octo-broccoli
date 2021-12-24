#include "Window.h"
#include "Map.h"
#include "Character.h"

/*
 *  Nous aurons une map de 944 pixels de large contre 624 pixels de hauteur en 16x16, nous affichons
 *  en 64x64(tile map déjà faite comme ça). Donc cela nous fait 59 blocs de large et 39 blocks de hauteur.
 *  Il y a donc une map de 59*64=3776 pixels de large et 39*64=2496 pixels de hauteur. 
 *  Tous ces pixels ne seront cependant pas affichés car la fenetre n'affichera que 3 immeubles de large et 1 immeuble + une route de hauteur.
 *  Cela fait donc une fenêtre de 3*6*1*64=1152 pixels de large et (8+4)*64=768 pixels de hauteur.
 *  Chaque case de 64*64 correspond à une classe définie: Immeuble, Route, voiture, Décor...
 *  Un immeuble n'est pas un décor (comme la route par exemple) car on peut interagir avec lui, pour entrer chez les boss.
 *  Nous aurons un vecteur géant 2D qui nous servira de map, permettant de situer n'importe quel élément et accéder directement
 *  aux fonctions de sa classe, l'affichage sera géré par les classes (constructeurs), collisions de même. 
 *  Pour cela nous aurons une classe mère, la classe Map qui servira de mère pour toutes les autres classes et ainsi créer un
 *  vecteur de la classe "Map". 
 *             
 */


int main(){

	// on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(1152, 768), "EcoBehave");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);	
	sf::View view = window.getDefaultView();
    window.setView(view);

    // on crée la TileWindow avec le niveau précédemment défini
    TileMap map("images/Ville_proto1.png", 59, 39);
    TileCharacter perso("perso_Fleche");

    map = map.load_map();
    perso = perso.load_character(Face);

    // Flags for key pressed
    bool upFlag    = false;
    bool downFlag  = false;
    bool leftFlag  = false;
    bool rightFlag = false;

    // on gère les évènements   
	sf::Event event;
    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Escape){
                window.close();
            }          
            // Si on appuit sur une touche
            if (event.type == sf::Event::KeyPressed){
                switch (event.key.code){
                    case sf::Keyboard::Up :     upFlag=true; break;
                    case sf::Keyboard::Down:    downFlag=true; break;
                    case sf::Keyboard::Left:    leftFlag=true; break;
                    case sf::Keyboard::Right:   rightFlag=true; break;
                    default : break;
                }
            }

            // Si on relache la touche
            if (event.type == sf::Event::KeyReleased){
                switch (event.key.code){
	                // Process the up, down, left and right keys
	                case sf::Keyboard::Up :     upFlag=false; break;
	                case sf::Keyboard::Down:    downFlag=false; break;
	                case sf::Keyboard::Left:    leftFlag=false; break;
	                case sf::Keyboard::Right:   rightFlag=false; break;
	                default : break;
                }
            }
            
        }

        if(leftFlag){  // left key is pressed: move our character
            view.move(-3.f, 0.f);
            perso = perso.load_character(Left);
        }
        else if(rightFlag){  // right key is pressed: move our character
            view.move(3.f, 0.f);
            perso = perso.load_character(Right);
        }
        else if(upFlag){     // up key is pressed: move our character
            view.move(0.f, -3.f);
            perso = perso.load_character(Back);
        }
        else if(downFlag){   // down key is pressed: move our character
            view.move(0.f, 3.f);
            perso = perso.load_character(Face);              
        }


        window.setView(view);

        // on dessine le niveau
        window.clear();
        window.draw(map);

        sf::Vector2f center = view.getCenter();
        sf::Vector2f offsetCenter(-64, -64);
	    perso.setPosition(center+offsetCenter);
        window.draw(perso);

        window.display();
    }

    return 0;
}