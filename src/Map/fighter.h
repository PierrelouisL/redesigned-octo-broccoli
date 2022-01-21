/**
 * @file fighter.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "Window.h"
#include "Character.h"
//#include "bot.h"

#define VICTOIRE 1
#define DEFAITE 2
#define TEMPO_MESS 3

typedef enum{
    UP, DOWN, RIGHT, LEFT, RETURN_
}text_pos;

class fighter : public TileCharacter
{
public:
    fighter();
	fighter(TileCharacter& character);
    sf::String get_atk(int nb);
	sf::String phrase_fin(int issue_du_match);
	int get_PV();
	void subit_atq(int dmg);
	sf::String get_Desc_Atq(int nb);
	int get_dmg_atq(int nb);
	int get_pourcent_PV();
	void aff_message(sf::RenderWindow* win, int nb_atq);
	void aff_fin(sf::RenderWindow* window, int issue_du_match);
	void heal(){HP = HP_base;}
private:
    sf::String atk_name[4];
    int HP_base;            // Initial HP for hp bar
    int HP;
    int atk_dmg[4];         // Amount of dmg for each attack
    sf::String atk_desc[8]; // Description for each attack
    bool bot;               // Is it a bot or not?
};

typedef enum
{
	MES_PLAYER,
	MES_ENNEMY,
	NOTHING
}state_act;

////// Prototype fonctions /////
void aff_background(sf::RenderWindow *window);

// Retourne -1 si un des personnage est mort donc on quitte, 0 sinon
int aff_combat(sf::RenderWindow *window, fighter* joueur, fighter* ennemi);

int handleEvents(sf::Event event);

void blink(sf::Uint8 *A, char *blinking_way);

void flagHandler(char flag, int *last_pos, sf::Text *Atq, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, char last_pressed);

// Actualise la barre d'hp du joueur ou de l'ennemi who = false pour ennemi who = true pour joueur
sf::RectangleShape aff_hp(sf::RenderWindow* window, fighter perso, bool who);

int fight_scene(sf::RenderWindow* window, fighter* joueur, fighter* ennemi);