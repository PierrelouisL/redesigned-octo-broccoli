#include "main_map.h"


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
    std::cout << "bonjour sur la nouvelle branche!" << std::endl;
	// on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(1152, 768), "EcoBehave");
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);	
	sf::View view = window.getDefaultView();
    window.setView(view);

    // on crée les objects qu'on va manipuler
    TileMap map("images/Map1.png", 60, 61);
    TileMap map_decors("images/Map2.png", 60, 61);
    TileCharacter perso("Greta");           // Character mode normal
    TileCharacterMario persoMario(perso);   // Same Character mode mario
    TileCharacter *ptr_perso = &perso;      // Object that we will manipulate
    TileElement element;
    Gamemode g_mode = normal;

    map.load_map();
    map_decors.load_map();
    ptr_perso->load_character();

    view.setCenter(sf::Vector2f(4.5*64, 30.5*64));  // Start at home
    ptr_perso->init_coord(view);
    //perso2.init_coord(view);
    //--
    bot bots(HARD); // Difficulté des bots (nb de spawn pour l'instant)

    // on gère les évènements   
	sf::Event event;
    sf::Clock clk;
    sf::Music music;
    sf::Music sound_effect;
    // on fait tourner la boucle principale

    while (window.isOpen()){

        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                printf("C'est chao\n");
                window.close();
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::A){  // Action key = A

                    sf::Vector2f next_case = ptr_perso->checkFrontCase(4, false);                  // Tree spawn
                    if( next_case != sf::Vector2f(-1, -1) ){
                        
                        obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = -1;

                        TileMap temp_element;
                        int level[] = { 0, 1 };
                        
                        if(!temp_element.load("images/arbre.png", level, 1, 2)){
                            std::cout << "Erreur du chargement de l'élément" << std::endl;
                        }

                        temp_element.setPosition(sf::Vector2f((int) (next_case.x/64)*64, (int) ((next_case.y)/64)*64) + sf::Vector2f(-2, -80));         
                        element.put_VectorElement(temp_element);
                        element.put_VectorType(4);
                    }

                    switch(g_mode){
                        case normal:
                                 
                            if( ptr_perso->checkFrontCase(-2, false) != sf::Vector2f(-1, -1) ){         // City to Trump's room 
                                view.setCenter(sf::Vector2f(7*64, 57.5*64));
                            
                            }
                            else if( ptr_perso->checkFrontCase(-3, false) != sf::Vector2f(-1, -1) ){         // Trump's room to City
                                view.setCenter(sf::Vector2f(22*64, 11.5*64));
                            
                            }           
                            else if( ptr_perso->checkFrontCase(3, false) != sf::Vector2f(-1, -1) ){          // Camera event
                                if(ptr_perso->get_eye() == TileCharacter::Left){

                                    music.openFromFile("sound/discours_Greta.wav");
                                    music.setVolume(100.f);
                                    music.play();
                                    while(music.getStatus() == sf::Music::Playing);
                                }
                            }
                            else if( ptr_perso->checkFrontCase(10, false) != sf::Vector2f(-1, -1) ){         // TP at the start of mario event
                                g_mode = mario;
                                view.setCenter(sf::Vector2f(22*64, 56.5*64));
                                music.openFromFile("sound/SuperMarioBros.wav");
                                music.setVolume(50.f);
                                music.play();
                                ptr_perso = &persoMario;
                            }
                            break;

                        case mario :

                            if( ptr_perso->checkFrontCase(11, false) != sf::Vector2f(-1, -1) ){         // TP to House
                                g_mode = normal;
                                view.setCenter(sf::Vector2f(4.5*64, 30.5*64));
                                music.stop();
                                ptr_perso = &perso;
                            }

                            else if( ptr_perso->checkFrontCase(12, false) != sf::Vector2f(-1, -1) ){
                                clk.restart();            
                                sound_effect.openFromFile("sound/MushroomSound.wav");
                                sound_effect.setVolume(5.f);
                                for(int i=0; i<4; i++){
                                    sound_effect.play(); 
                                    ptr_perso->scale( sf::Vector2f(2, 2));
                                    ptr_perso->setPosition( view.getCenter()+sf::Vector2f(-64*2*(i*i+1), -64*2*(i+1+1)) );
                                    window.setActive();
                                    window.clear();
                                    window.draw(map);
                                    window.draw(*ptr_perso);
                                    window.display();
                                    clk.restart();
                                    while(clk.getElapsedTime().asSeconds() < 2);
                                }
                                sound_effect.openFromFile("sound/BallonBoom.wav");
                                sound_effect.setVolume(80.f);
                                sound_effect.play(); 
                                ptr_perso->setScale( sf::Vector2f(1, 1));
                                view.setCenter(sf::Vector2f(22*64, 56.5*64));
                            }  
                            break;

                        case fight :
                            break;

                        default :
                            break;
                    }
                }

                
                if(ptr_perso->oneMoveFlag()){
                    sf::Vector2f next_case;
                    switch(g_mode){

                        case normal :
                            next_case = ptr_perso->checkFrontCase(5, false);                  // Car event
                            if( next_case != sf::Vector2f(-1, -1) ){

                                obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = 0;

                                TileMap temp_element;
                                int level[] = { 0, 1, 2, 3};
                                
                                if(!temp_element.load("images/voiture.png", level, 2, 2)){
                                    std::cout << "Erreur du chargement de l'élément voiture" << std::endl;
                                }

                                temp_element.setPosition(sf::Vector2f((int) (next_case.x/64)*64, (int) ((next_case.y)/64)*64) + sf::Vector2f(640, -64));        
                                element.put_VectorElement(temp_element);
                                element.put_VectorType(5);
                            }
                            break;

                        case mario : 
                            break;

                        case fight :
                            break;

                        default :
                            break;
                    }
                }
            }
    
            ptr_perso->checkKeyMove(event);  // Check status of movement key
            //bots.check_and_follow(perso);
        }
        window.setActive();
        ptr_perso->move(view);           // Move character

        // on dessine le niveau
        window.setView(view);
        window.clear();
        window.draw(map);
   
        ptr_perso->setPosition( view.getCenter()+sf::Vector2f(-64, -64) );   // Set the middle of the character in the middle of the view
        //std::cout << "x=" << (int)view.getCenter().x/64 << "y = " << (int)view.getCenter().y/64 << std::endl;
        //bots.check_and_follow(perso);
        //perso2.setPosition(sf::Vector2f(192,2304 ));
        //window.draw(perso2);
        window.draw(*ptr_perso);

        element.load_allElement(window);
        //bots.draw(window);

        window.draw(map_decors);
        window.display();
    }

    return 0;
}