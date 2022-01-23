#pragma once
#include "Window.h"
#include "fighter.h"

class fight_scene
{
    // Utility functions unused outside class
    int aff_combat(sf::RenderWindow *window, fighter* joueur, fighter* ennemi, std::vector<sf::Text*> Atq);
    void blink(sf::Uint8 *A, char *blinking_way);
    void flagHandler(char flag, int *last_pos, std::vector<sf::Text*> Atq, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, char last_pressed);
    void goodbye();
    sf::RectangleShape aff_hp(sf::RenderWindow* window, fighter perso, bool who);
private:

    // Rendering 
    sf::Font NiceFont;
    std::vector<sf::Text*> Atq;
    sf::Texture *Background;
    sf::Sprite *Background_sprite;
    sf::Texture *Hp;
    sf::Sprite *Hp_Sprite;
    sf::Sprite *Hp2_Sprite;
    sf::Text *nom_joueur;
    sf::Text *nom_pollueur;


    // Flags for key pressed
    bool upFlag = false;
    bool downFlag = false;
    bool leftFlag = false;
    bool rightFlag = false;
    bool returnFlag = false;
    char actionFlag = NOTHING; // Si une action est en cours on ne gere plus les evenements!


public:
    fight_scene(/* args */);
    int handleEvents(sf::Event event);
    void Display(sf::RenderWindow* window, fighter* player, fighter* currentbot);
    ~fight_scene();
};

void printf_s(std::string msg);
