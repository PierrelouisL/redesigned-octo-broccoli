#include "main_map.h"

#define FIGHT_ENABLED  // A commenter si tu veux pas de combat!
#define DEBUG

//sf::Mutex WinMutex; // We ensure that we finished drawing before drawing in another thread!
//sf::Mutex Console; // We ensure that we finished drawing before drawing in another thread!

bool quit = false;

Gamemode g_mode = menu_;
bot bots(HARD); // Difficulté des bots (nb de spawn pour l'instant

/*void Thread_fight(sf::RenderWindow* window, fighter* player){
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
}*/

int main(){

	// on crée la fenêtre
    sf::RenderWindow window(sf::VideoMode(1152, 768), "redesigned-octo-broccoli");
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);	
	sf::View view = window.getDefaultView();
    window.setView(view);

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
    std::cout << "printing bot" << std::endl;
    bots.print();

    bots.current_bot()->alive = false;
    
    element.sound_LoadStart(music, "sound/AnimalCrossing.wav", 80.f, true);
    
    while (window.isOpen() && !quit){
        if(g_mode == normal || g_mode == mario){
            //WinMutex.lock();
            while (window.pollEvent(event)){
                if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                    printf("C'est chao\n");
                    window.close();
                    quit = true;
                }
                if(event.type == sf::Event::KeyPressed){
                    if(event.key.code == sf::Keyboard::Space){  // Action key = space

                        sf::Vector2f next_case = ptr_perso->checkFrontCase(4, false);                  // Tree spawn
                        if( next_case != sf::Vector2f(-1, -1) ){

                            player->heal(); // Spawning a tree makes you get healed

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
                        switch(g_mode){
                            case normal:

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
                                    ptr_perso = &perso;
                                    ptr_perso->resetkey();
                                }

                                else if( ptr_perso->checkFrontCase(12, false) != sf::Vector2f(-1, -1) ){    // Ear mario mushroom event
                                    clk.restart();            
                                    element.sound_LoadStart(sound_effect, "sound/MushroomSound.wav", 5.f, false);
                                    for(int i=0; i<4; i++){
                                        ptr_perso->scale( sf::Vector2f(2, 2));
                                        ptr_perso->setPosition( view.getCenter()+sf::Vector2f(-64*2*(i*i+1), -64*2*(i+1+1)) );
                                        window.setActive();
                                        window.clear();
                                        window.draw(map);
                                        window.draw(*ptr_perso);
                                        window.display();
                                        clk.restart();
                                        while(clk.getElapsedTime().asSeconds() < 2);
                                        sound_effect.play();
                                    }
                                    element.sound_LoadStart(sound_effect, "sound/BallonBoom.wav", 80.f, false);                                
                                    ptr_perso->setScale( sf::Vector2f(1, 1));
                                    view.setCenter(sf::Vector2f(22*64, 56.5*64));
                                }  
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

                                next_case = ptr_perso->checkFrontCase(6, false);                    // Glitch map event
                                if(  next_case != sf::Vector2f(-1, -1) ){

                                    obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = 0;
                                    
                                    element.sound_LoadStart(sound_effect, "sound/SpecialSoundEffect.wav", 80.f, false);  
                                    view.zoom(3);
                                }
                            default :
                                break;
                        }
                    }
                }
                sf::Vector2f next_case;
                next_case = ptr_perso->checkFrontCase(8, false);
                if( next_case != sf::Vector2f(-1, -1)){
                    obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = 0;
                    bots.which_bot(next_case); // We check which bot is detected and store it in the bots.current_bot();
                    ptr_perso->resetkey();
                    g_mode = fight;
                }
                ptr_perso->checkKeyMove(event);  // Check status of movement key
            }

           
            window.setActive();
            ptr_perso->move(view);           // Move character

            // on dessine le niveau
            window.setView(view);
            window.clear();
            window.draw(map);
            bots.draw(window);

            ptr_perso->setPosition( view.getCenter()+sf::Vector2f(-64, -64) );   // Set the middle of the character in the middle of the view
            window.draw(*ptr_perso);

            element.load_allElement(window);
            if(element.check_collision(ptr_perso->getPosition())){
                // Collision so player gets hurt!
                player->subit_atq(2);
                view.move(-5, 0);
                std::cout << "Ouch you just hit a car!" << std::endl;
            }
            
            window.draw(map_decors);
            allGoal.display_goal(window, view.getCenter());

            window.display();
            //WinMutex.unlock();
        }
        else if(g_mode == menu_){
            menu *Ecran_menu = new menu;
            Ecran_menu->Display(window);
            delete Ecran_menu;
            g_mode = normal;
        }
        else if(g_mode == fight){
            fight_scene *f_sc = new fight_scene;
            while(g_mode == fight){
                while(window.pollEvent(event)){
                    if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                        //printf_s("Adios!");
                        g_mode = normal;
                        quit = true;
                        window.close();
                    }
                    f_sc->handleEvents(event);
                }
                f_sc->Display(window, player, bots.current_bot());
            }
            ptr_perso->resetkey();
            delete f_sc;
        }
        
    }
    std::cout << "le vrai chao!"<< std::endl;
    return 0;
}