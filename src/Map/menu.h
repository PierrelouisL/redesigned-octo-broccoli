#pragma once
#include "Window.h"

typedef enum{
    intro, play, credits
}sel;

extern Gamemode g_mode;
extern bool quit;
extern sf::Mutex Console; // We ensure that we finished drawing before drawing in another thread!


class menu
{
    void rotate_circle(float theta);
    void update_displayed_text();
    void update_arrow();
private:
    // Rendering 
    sf::Font TextFont;
    sf::Font SelFont;
    std::vector<sf::Text*> Menu_options;
    std::vector<sf::Text*> Menu_text;
    sf::Texture *Background;
    sf::Sprite *Background_sprite;
    sf::Texture *Brocco_T; // Broccoli texture from image file
    std::vector<sf::Sprite*> Brocco_S; // Broccoli sprite from texture to draw (8 of them will be displayed)
    sf::Texture *Sel_arrow_T;
    sf::Sprite *Sel_arrow_S;
    sel selected;

    float rotation; // Rotation angle
    float rotation2; // Rotation but on itself

    bool _upFlag;
    bool _downFlag;
    bool _returnFlag;
    
public:
    menu();
    void Display(sf::RenderWindow* window);
    ~menu();
};

