#include <stdlib.h>
#include "Window.h"
#include "Character.h"
#include "Map.h"
#include "Element.h"



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
    window.setFramerateLimit(45);
    window.setVerticalSyncEnabled(true);	
	sf::View view = window.getDefaultView();
    window.setView(view);

    // on crée les objects qu'on va manipuler
    TileMap map("images/Ville1.png", 59, 39);
    TileMap map_decors("images/Ville2.png", 59, 39);
    TileCharacter perso("perso_debug");
    TileElement element;

    map.load_map();
    map_decors.load_map();
    perso.load_character();

    //--
    view.setCenter(sf::Vector2f(3.5*64, 30.5*64));  // Correspond with the bottom left corner (the map ville_proto1 start)
    perso.init_coord(view);
    //--

    // on gère les évènements   
	sf::Event event;
    // on fait tourner la boucle principale
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                printf("C'est chao\n");
                window.close();
            }
            
            perso.actionKey(event, element);         
            perso.checkKeyMove(event);  // Check status of movement key
        }

        perso.move(view);           // Move character
        //perso.checkFrontCase();

        // on dessine le niveau
        window.setView(view);
        window.clear();
        window.draw(map);
   
        perso.setPosition( view.getCenter()+sf::Vector2f(-64, -64) );   // Set the middle of the character in the middle of the view
        window.draw(perso);

        element.load_allElement(window);

        window.draw(map_decors);
        window.display();
    }

    return 0;
}