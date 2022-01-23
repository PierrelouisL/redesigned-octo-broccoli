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

#define FIGHT_ENABLED  // A commenter si tu veux pas de combat!
#define DEBUG

bool quit = false;

bot bots(HARD); // Difficulté des bots (nb de spawn pour l'instant

sf::Mutex WinMutex; // We ensure that we finished drawing before drawing in another thread!
sf::Mutex Console; // We ensure that we finished drawing before drawing in another thread!

Gamemode g_mode = menu_;

void Thread_fight(sf::RenderWindow* window, fighter* player){
    fight_scene f_sc;
    sf::Event event;
    while(!quit){
        if(g_mode == fight){
        while(window->pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                printf_s("C'est chao");
                quit = 1;
                window->close();
            }
            printf_s("polling");
            f_sc.handleEvents(event);
        }
            printf_s("LETS GO!");
            f_sc.Display(window, player, bots.current_bot());
        }
        WinMutex.unlock();
    }
    return;
}

void Thread_menu(sf::RenderWindow* window){
    std::cout << "Thread lancé !" << std::endl;
    WinMutex.lock();
    menu Ecran_menu;
    Ecran_menu.Display(window);
    g_mode = normal;
    WinMutex.unlock();
    printf_s("we quit!");
}



int main(){
	// on crée la fenêtre
    sf::RenderWindow* window = new sf::RenderWindow;
	window->create(sf::VideoMode(1152, 768), "redesigned-octo-broccoli");
    window->setFramerateLimit(120);
    window->setVerticalSyncEnabled(true);	
	sf::View view = window->getDefaultView();
    window->setView(view);

    // on crée les objects qu'on va manipuler
    TileMap map("images/Map/Map1.png", 60, 61);
    TileMap map_decors("images/Map/Map2.png", 60, 61);
    TileCharacter perso("Greta");           // Character mode normal
    TileCharacterMario persoMario(perso);   // Same Character mode mario
    TileCharacter *ptr_perso = &perso;      // Object that we will manipulate
    TileElement element;
    TileGoal allGoal;

    map.load_map();
    map_decors.load_map();
    ptr_perso->load_character();

    view.setCenter(sf::Vector2f(4.5*64, 30.5*64));  // Start at home
    ptr_perso->init_coord(view);
    fighter* player = new fighter;
    // on gère les évènements et music
	sf::Event event;
    sf::Clock clk;
    sf::Music music;
    sf::Music sound_effect;
    // on fait tourner la boucle principale
    bots.print();

    sf::Thread thread(std::bind(&Thread_fight, window, player));
    thread.launch();
    sf::Thread t_menu(std::bind(&Thread_menu, window));
    t_menu.launch();
    bots.current_bot()->alive = false;
    bool heal = false;
    element.sound_LoadStart(music, "sound/AnimalCrossing.wav", 80.f, true);
    while (window->isOpen() && !quit){
        WinMutex.lock();
        while (window->pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                printf("C'est chao\n");
                window->close();
            }

            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::A){  // Action key = A

                    sf::Vector2f next_case = ptr_perso->checkFrontCase(4, false);                  // Tree spawn
                    if( next_case != sf::Vector2f(-1, -1) ){

                        //ptr_perso->heal(); // Spawning a tree makes you get healed

                        element.sound_LoadStart(sound_effect, "sound/Tree.wav", 25.f, false);

                        obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = -1;

                        TileMap temp_element;
                        int level[] = { 0, 1 };
                        
                        temp_element.load("images/Decors/arbre.png", level, 1, 2);
                        temp_element.setPosition(sf::Vector2f((int) (next_case.x/64)*64, (int) ((next_case.y)/64)*64) + sf::Vector2f(-2, -80));         
                        element.put_VectorElement(temp_element);
                        element.put_VectorType(4);

                        allGoal.add_tree();
                        if(allGoal.get_goalTree()){
                            map.change_map("images/Map/Map3.png");
                            map.load_map();

                            for(int i=0; i<7; i++){
                                obstacle_ville1[10][19+i] = -2;
                            }
                        }
                    }
                    bots.check_and_follow(perso.getPosition());
                    switch(g_mode){
                        case normal:
                            if(bots.current_bot()->alive){
                                g_mode = fight;
                            }

                            if( ptr_perso->checkFrontCase(-2, false) != sf::Vector2f(-1, -1) ){             // City to Trump's room 
                                element.sound_LoadStart(music, "sound/HymneEtatUnis.wav", 20.f, true);
                                view.setCenter(sf::Vector2f(7*64, 57.5*64));
                            
                            }
                            else if( ptr_perso->checkFrontCase(-3, false) != sf::Vector2f(-1, -1) ){        // Trump's room to City
                                element.sound_LoadStart(music, "sound/AnimalCrossing.wav", 80.f, true);
                                view.setCenter(sf::Vector2f(22*64, 11.5*64));
                            
                            }           
                            else if( ptr_perso->checkFrontCase(3, false) != sf::Vector2f(-1, -1) ){         // Camera event
                                if(ptr_perso->get_eye() == TileCharacter::Left){
                                    allGoal.done_goalCamera();
                                    element.sound_LoadStart(sound_effect, "sound/discours_Greta.wav", 80.f, false);
                                    while(music.getStatus() == sf::Music::Playing);
                                }
                            }
                            else if( ptr_perso->checkFrontCase(10, false) != sf::Vector2f(-1, -1) ){        // TP at the start of mario event
                                g_mode = mario;
                                view.setCenter(sf::Vector2f(22*64, 56.5*64));
                                element.sound_LoadStart(music, "sound/SuperMarioBros.wav", 50.f, true);
                                ptr_perso = &persoMario;
                            }
                            break;

                        case mario :

                            if( ptr_perso->checkFrontCase(11, false) != sf::Vector2f(-1, -1) ){         // TP to House
                                element.sound_LoadStart(music, "sound/AnimalCrossing.wav", 80.f, true);

                                g_mode = normal;
                                view.setCenter(sf::Vector2f(4.5*64, 30.5*64));
                                music.stop();
                                ptr_perso = &perso;
                            }

                            else if( ptr_perso->checkFrontCase(12, false) != sf::Vector2f(-1, -1) ){
                                clk.restart();            
                                element.sound_LoadStart(sound_effect, "sound/MushroomSound.wav", 5.f, false);
                                for(int i=0; i<4; i++){
                                    ptr_perso->scale( sf::Vector2f(2, 2));
                                    ptr_perso->setPosition( view.getCenter()+sf::Vector2f(-64*2*(i*i+1), -64*2*(i+1+1)) );
                                    window->setActive();
                                    window->clear();
                                    window->draw(map);
                                    window->draw(*ptr_perso);
                                    window->display();
                                    clk.restart();
                                    while(clk.getElapsedTime().asSeconds() < 2);
                                }
                                element.sound_LoadStart(sound_effect, "sound/BallonBoom.wav", 80.f, false);                                
                                ptr_perso->setScale( sf::Vector2f(1, 1));
                                view.setCenter(sf::Vector2f(22*64, 56.5*64));
                            }  
                            break;

                        case fight :
                            if(!bots.current_bot()->alive){
                                g_mode = normal;
                            }
                            break;
                        case menu_:
                            // We don't do anything here
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

                                element.sound_LoadStart(sound_effect, "sound/Car.wav", 80.f, false);  

                                obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = 0;

                                TileMap temp_element;
                                int level[] = { 0, 1, 2, 3};
                                
                                temp_element.load("images/Decors/voiture.png", level, 2, 2);
                                temp_element.setPosition(sf::Vector2f((int) (next_case.x/64)*64, (int) ((next_case.y)/64)*64) + sf::Vector2f(640, -64));        
                                element.put_VectorElement(temp_element);
                                element.put_VectorType(5);
                            }
                            next_case = ptr_perso->checkFrontCase(6, false);
                            if(  next_case != sf::Vector2f(-1, -1) ){

                                obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = 0;
                                
                                element.sound_LoadStart(sound_effect, "sound/SpecialSoundEffect.wav", 80.f, false);  
                                view.zoom(3);
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
        window->setActive();
        ptr_perso->move(view);           // Move character

        // on dessine le niveau
        window->setView(view);
        window->clear();
        std::cout << "drawing map!" << std::endl;
        window->draw(map);

        ptr_perso->setPosition( view.getCenter()+sf::Vector2f(-64, -64) );   // Set the middle of the character in the middle of the view
        //std::cout << "x=" << (int)view.getCenter().x/64 << "y = " << (int)view.getCenter().y/64 << std::endl;
        //bots.check_and_follow(perso);
        //perso2.setPosition(sf::Vector2f(192,2304 ));
        //window.draw(perso2);
        window->draw(*ptr_perso);

        element.load_allElement(*window);
        //bots.draw(window);

        window->draw(map_decors);
        allGoal.display_goal(*window, view.getCenter());

        window->display();
        WinMutex.unlock();
    }
    std::cout << "le vrai chao!"<< std::endl;
    exit(0);
    //thread.wait();
    delete window;
    return 0;
}