#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <functional> //std::bind
#include <iostream>
#include <vector>

#define VICTOIRE 1
#define DEFAITE 2

// Classe de test pour permettre de tester les combats! 
class classetest{ 
public:
    classetest();
    sf::String get_atq(int nb);
    sf::String phrase_fin(int issue_du_match);
    int get_PV();
    void subit_atq(int dmg);
    sf::String get_Desc_Atq(int nb);
    int get_dmg_atq(int nb);


private:
    sf::String atq[4]; // Nom de l'attaque
    int PV; // Points de vie
    int dmg_atq[4]; // degats de chaque attaque
    sf::String atq_desc[4]; // Description quand on lance l'attaque
};



typedef enum{
    UP, DOWN, RIGHT, LEFT
}position_texte;


////// Prototype fonctions /////
void aff_background(sf::RenderWindow* window);

void aff_combat(sf::RenderWindow* window);

void handleEvents(sf::Event event);
