#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <functional> //std::bind
#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

#define VICTOIRE 1
#define DEFAITE 2
#define TEMPO_MESS 3


// Classe de test pour permettre de tester les combats!
class classetest
{
public:
	classetest();
	sf::String get_atq(int nb);
	sf::String phrase_fin(int issue_du_match);
	int get_PV();
	void subit_atq(int dmg);
	sf::String get_Desc_Atq(int nb);
	int get_dmg_atq(int nb);
	int get_pourcent_PV();
	void aff_message(sf::RenderWindow* win, int nb_atq);
	void aff_fin(sf::RenderWindow* window, int issue_du_match);

private:
	sf::String atq[4];		// Nom de l'attaque
	int PV_base;	 			// PV initiaux pour pourcent
	int PV;						// Points de vie
	int dmg_atq[4];			// degats de chaque attaque
	sf::String atq_desc[8]; // Description quand on lance l'attaque
};

typedef enum
{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	RETURN_
} position_texte;

typedef enum
{
	MES_JOUEUR,
	MES_ENNEMI,
	RIEN
} etat_action;

////// Prototype fonctions /////
void aff_background(sf::RenderWindow *window);

// Retourne -1 si un des personnage est mort donc on quitte, 0 sinon
int aff_combat(sf::RenderWindow *window, classetest* joueur, classetest* ennemi);
void aff_hp(sf::RenderWindow *window);

int handleEvents(sf::Event event);

void blink(sf::Uint8 *A, char *blinking_way);

void flagHandler(char flag, int *last_pos, sf::Text *Atq, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, char last_pressed);

// Actualise la barre d'hp du joueur ou de l'ennemi who = false pour ennemi who = true pour joueur
sf::RectangleShape aff_hp(sf::RenderWindow* window, classetest perso, bool who);
