#include <stdlib.h>
#include "Window.h"
#include "Character.h"
#include "Map.h"
#include "Element.h"
#include "bot.h"
#include "fighter.h"

#include <thread>
#include <mutex>


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

typedef enum{MENU, CITY, FIGHT, END}States;
States Actual_state = CITY;

bool fight = false; //temp
bool quit = false;

bot bots(HARD); // Difficulté des bots (nb de spawn pour l'instant

sf::Mutex WinMutex; // We ensure that we finished drawing before drawing in another thread!
sf::Mutex Console; // We ensure that we finished drawing before drawing in another thread!

void printf_s(std::string msg){
    Console.lock();
    std::cout << msg << std::endl;
    Console.unlock();
}

void Thread_menu(sf::RenderWindow* window){

}

void Thread_city(sf::RenderWindow* window){
    /*TileMap map("images/Ville1.png", 59, 39);
    TileMap map_decors("images/Ville2.png", 59, 39);
    map.load_map();
    map_decors.load_map();
    while(!quit){
        if(Actual_state == CITY){
            std::cout << "we try to print!" << std::endl;
            { // Local mutex to draw behind
                std::lock_guard<std::mutex> iolock(DrawBehindMutex);
                window->setActive(true);
                std::cout << "we printin" << std::endl;
                window->draw(map);
                window->setActive(false);
            } // Changing scope
            { // Local mutex to draw in front
                std::lock_guard<std::mutex> iolock(DrawInFrontMutex);
                window->setActive(true);
                window->draw(map_decors);
                window->setActive(false);
            }
        }
    }*/
}

/*void fight_init(sf::Texture *Background, sf::Sprite *Background_sprite, sf::Texture *Hp, sf::Sprite *Hp_Sprite, ){
    //NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");

}*/

void Thread_fight(sf::RenderWindow* window, fighter* player){
    sf::Font NiceFont;
    NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");
    fight_init();
    //fighter* player = new fighter;
    // Allocation des textures -> Background, texte, hp
	// Allocation background
	sf::Texture *Background = new sf::Texture;
	Background->loadFromFile("images/background_combat_ville.png");
	sf::Sprite *Background_sprite = new sf::Sprite;
	Background_sprite->setTexture(*Background);

	// Allocation HP1
	sf::Texture *Hp = new sf::Texture;
	Hp->loadFromFile("images/hpbar.png");
	sf::Sprite *Hp_Sprite = new sf::Sprite;
	Hp_Sprite->setTexture(*Hp);
	Hp_Sprite->setPosition(sf::Vector2f(50.f, 0.f));

	// Allocation HP2
	sf::Sprite *Hp2_Sprite = new sf::Sprite;
	Hp2_Sprite->setTexture(*Hp);
	Hp2_Sprite->setPosition(sf::Vector2f(840.f, 0.f));

	sf::Text nom_joueur(sf::String("Joueur"), NiceFont, 20);
	nom_joueur.setPosition(sf::Vector2f(120.f, 10.f));
	sf::Text Pollueur(sf::String("Pollueur"), NiceFont, 20);
	Pollueur.setPosition(sf::Vector2f(910.f, 10.f));
    sf::Event event;

    std::vector<sf::Text*> Atq;
    for(int i = 0; i< 4; ++i){
        Atq.push_back(new sf::Text);
        Atq[i]->setFont(NiceFont);
        Atq[i]->setCharacterSize(40);
    }
    Atq[0]->setPosition(sf::Vector2f(20.f, 510.f));
    Atq[1]->setPosition(sf::Vector2f(600.f, 510.f));
    Atq[2]->setPosition(sf::Vector2f(20.f, 610.f));
    Atq[3]->setPosition(sf::Vector2f(600.f, 610.f));
    while(!quit){
        if(Actual_state == FIGHT){
        while(window->pollEvent(event)){
            if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                printf_s("C'est chao");
                //printf("C'est chao\n");
                quit = 1;
                window->close();
            }
            printf_s("polling");
            //std::cout << "polling" << std::endl;
            handleEvents(event);
        }
            printf_s("LETS GO!");
            WinMutex.lock();
            window->setActive(true);
            window->clear();
            window->setView(window->getDefaultView());
            window->draw(*Background_sprite);
            if(aff_combat(window, player, bots.current_bot(), Atq) < 0){
                sf::Clock clk_fin;
                sf::RectangleShape HideMes(sf::Vector2f(1142.f, 200.f));
                HideMes.setFillColor(sf::Color(200, 226, 226, 255));
                HideMes.setPosition(sf::Vector2f(5.f, 499.f));
                window->draw(HideMes);
                if(player->get_PV() < 0){
                    std::cout << "le joueur est mort" << std::endl;
                    player->aff_fin(window, VICTOIRE); // A remplacer  plus tard
                }else{
                    std::cout << "Le pollueur est mort bien vu" << std::endl;
                    bots.current_bot()->aff_fin(window, DEFAITE);
                }
                window->display();
                while(clk_fin.getElapsedTime().asSeconds() < 1); // Petit délai de 10s
                goodbye();
                Actual_state == CITY;
                bots.current_bot()->alive = false;
                WinMutex.unlock();
                window->setActive(false);
                // On passe à l'état city et on attend qu'on revienne pour repartir!
            }
            #ifdef DEBUG
            std::cout <<"drawing.."<< std::endl;
            #endif
            window->draw(*Hp_Sprite);
            window->draw(*Hp2_Sprite);
            window->draw(nom_joueur);
            window->draw(Pollueur);
            window->display();
            window->setActive(false);
        }
        WinMutex.unlock();
    }
}


void Thread_end(sf::RenderWindow* window){
    return;
}



int main(){
    sf::Clock clk;
    std::cout << "bonjour sur la nouvelle branche!" << std::endl;
	// on crée la fenêtre
    sf::RenderWindow* window = new sf::RenderWindow;
	window->create(sf::VideoMode(1152, 704),
						"Petage de gueule en regle des pollueurs");
    window->setFramerateLimit(45);
    window->setVerticalSyncEnabled(true);	
	sf::View view = window->getDefaultView();
    window->setView(view);
    sf::Time elapsed = clk.getElapsedTime();
    std::cout << "creating window = " << elapsed.asMilliseconds() << " ms" << std::endl;


    // on crée les objects qu'on va manipuler
    TileCharacter perso2("perso_debug");
    perso2.load_character();
    elapsed = clk.getElapsedTime() - elapsed;
    std::cout << "creating perso = " << elapsed.asMilliseconds() << " ms" << std::endl;

    TileMap map("images/Ville1.png", 59, 39);
    TileMap map_decors("images/Ville2.png", 59, 39);
    elapsed = clk.getElapsedTime() - elapsed;
    std::cout << "creating map = " << elapsed.asMilliseconds() << " ms" << std::endl;

    TileCharacter perso("perso_debug");
    TileElement element;
    elapsed = clk.getElapsedTime() - elapsed;
    std::cout << "creating perso2 = " << elapsed.asMilliseconds() << " ms" << std::endl;

    
    map.load_map();
    map_decors.load_map();
    elapsed = clk.getElapsedTime() - elapsed;
    std::cout << "load map = " << elapsed.asMilliseconds() << " ms" << std::endl;
    perso.load_character();

    //--
    view.setCenter(sf::Vector2f(3.5*64, 30.5*64));  // Correspond with the bottom left corner (the map ville_proto1 start)
    perso.init_coord(view);
    //perso2.init_coord(view);
    //--
    elapsed = clk.getElapsedTime() - elapsed;
    std::cout << "init perso = " << elapsed.asMilliseconds() << " ms" << std::endl;
    fighter joueur(perso);
    // on gère les évènements   
	sf::Event event;
    // on fait tourner la boucle principale
    bots.print();
    elapsed = clk.getElapsedTime() - elapsed;
    std::cout << "print bot = " << elapsed.asMilliseconds() << " ms" << std::endl;


    //std::thread t_city(Thread_city, window);
    //std::thread t_menu(Thread_menu, window);
    //std::thread t_fight(Thread_fight, window, &joueur);
    sf::Thread thread(std::bind(&Thread_fight, window, &joueur));
    //sf::Thread thread(&Thread_fight, window, &joueur);
    thread.launch();
    //std::thread t_end(Thread_end, window);
    //t_menu.join();
    //t_fight.join();
    //t_end.join();
    //t_city.join();
    bots.current_bot()->alive = false;
    while (window->isOpen() && !quit)
    {
        bots.check_and_follow(perso.getPosition());
        //Console.lock();
        //std::cout << "alive?" << bots.current_bot()->alive << std::endl;
        //Console.unlock();
        if(bots.current_bot()->alive){
            fight = true;
            Actual_state = FIGHT;
        }else{
            fight = false;
            Actual_state = CITY;
        }
        switch(Actual_state){
            case MENU:

                break;
            case CITY:
                window->setActive(true);
                while(window->pollEvent(event)){
                    if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                        printf("C'est chao\n");
                        quit = 1;
                        window->close();
                    }
                    printf_s("polling");
                    perso.actionKey(event, element);         
                    perso.checkKeyMove(event);  // Check status of movement key
                    handleEvents(event);
                }
                WinMutex.lock();
                perso.move(view);           // Move character
                //perso.checkFrontCase();

                window->setView(view);
                window->clear();
                window->draw(map);
                perso.setPosition( view.getCenter()+sf::Vector2f(-64, -64) );   // Set the middle of the character in the middle of the view
                //std::cout << "x=" << (int)view.getCenter().x/64 << "y = " << (int)view.getCenter().y/64 << std::endl;
                bots.draw(*window);
                window->draw(perso);

                element.load_allElement(*window);
                
                window->draw(map_decors);
                window->display();
                WinMutex.unlock();
                window->setActive(false);
                break;
            case FIGHT:
                //printf_s("entree en combat");
                #ifdef FIGHT_ENABLED
                perso.resetkey();
                if(!bots.current_bot()->alive){
                    // Bot dead so we move on
                    printf_s("bot dead");
                }else{
                    //printf_s("bot alive");
                }
                #endif
                break;
            case END:

                break;
        }
        /*
        bots.check_and_follow(perso.getPosition());
        std::cout << "alive?" << bots.current_bot()->alive << std::endl;
        if(bots.current_bot()->alive){
            fight = true;
        }else{
            fight = false;
        }
        //std::cout << fight << std::endl;
        if(fight){
            //std::cout << "entree combat" << std::endl;
            // Here we can disable the fights or not
            std::cout << "joeuru " << perso.getPosition().x << " " << perso.getPosition().y << std::endl;
            
            #ifdef FIGHT_ENABLED 
            if(fight_scene(&window, &joueur, bots.current_bot()) == VICTOIRE){
                // On a gagné le combat -> on détruit le bot
                std::cout << "victory" << std::endl;
                bots.rm_bot();
                joueur.heal();
            }else{
                // On est mort donc game over!
                std::cout << "game over!" << std::endl;

            }
            window.clear();
            #endif
            bots.print();
            std::cout << "fini combat" << std::endl;
            bots.current_bot()->alive = false;
            fight = false;
        }else{
            std::cout << "joeuru " << perso.getPosition().x << " " << perso.getPosition().y << std::endl;
            while (window.pollEvent(event))
            {
                if(event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)){
                    printf("C'est chao\n");
                    quit = 1;
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
            //std::cout << "x=" << (int)view.getCenter().x/64 << "y = " << (int)view.getCenter().y/64 << std::endl;
            bots.draw(window);
            //perso2.setPosition(sf::Vector2f(192,2304 ));
            //window.draw(perso2);
            window.draw(perso);

            element.load_allElement(window);


            window.draw(map_decors);
            window.display();
        }*/
    }
    free(window);
    return 0;
}