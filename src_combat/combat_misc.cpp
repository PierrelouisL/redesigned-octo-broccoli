#include "combat.h"

void blink(sf::Uint8 *A, char *blinking_way)
{
	if (*blinking_way)
	{ // Blinking_way = 1 donc on baisse la valeur
		if (*A >= 15)
		{
			*A -= 5;
		}
		else
		{
			*blinking_way = 0;
		}
	}
	else
	{
		if (*A <= 240)
		{
			*A += 5;
		}
		else
		{
			*blinking_way = 1;
		}
	}
}

void flagHandler(char flag, int *last_pos, sf::Text *Atq, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, char last_pressed)
{
	#ifdef DEBUG
	std::cout << (int)flag << "=f" << std::endl;
	#endif
	if (flag == UP)
	{ // Up
		Atq[*last_pos].setFillColor(sf::Color(R, G, B, 255));
		switch (*last_pos)
		{
		case 0:
			break; // On était deja en haut donc on bouge pas
		case 1:
			break; // On était deja en haut donc on bouge pas
		case 2:
			*last_pos = 0;
			break; // On monte d'une case
		case 3:
			*last_pos = 1;
			break; // On monte d'une case
		}
		last_pressed = UP;
	}
	else if (flag == DOWN)
	{ // Down
		Atq[*last_pos].setFillColor(sf::Color(R, G, B, 255));
		switch (*last_pos)
		{
		case 0:
			*last_pos = 2;
			break;
		case 1:
			*last_pos = 3;
			break;
		case 2:
			break;
		case 3:
			break;
		}
		last_pressed = DOWN;
	}
	else if (flag == RIGHT)
	{ // Right
		Atq[*last_pos].setFillColor(sf::Color(R, G, B, 255));
		switch (*last_pos)
		{
		case 0:
			*last_pos = 1;
			break;
		case 1:
			break;
		case 2:
			*last_pos = 3;
			break;
		case 3:
			break;
		}
		last_pressed = RIGHT;
	}
	else if (flag == LEFT)
	{ // Left
		Atq[*last_pos].setFillColor(sf::Color(R, G, B, 255));
		switch (*last_pos)
		{
		case 0:
			break;
		case 1:
			*last_pos = 0;
			break;
		case 2:
			break;
		case 3:
			*last_pos = 2;
			break;
		}
		last_pressed = LEFT;
	}
	else if (flag == RETURN_)
	{ // Return
	  // Nous venons d'appuyer sur enter donc nous devons gérer une attaque!
	}
}

// Actualise la barre d'hp du joueur ou de l'ennemi who = false pour ennemi who = true pour joueur
sf::RectangleShape aff_hp(sf::RenderWindow* window, classetest perso, bool who){
	sf::RectangleShape barre_hp(sf::Vector2f(172.f,22.f)); // Ce qui sera en vert pour afficher ce qu'il reste d'hp au perso
	int PV = perso.get_PV();
	float size = ((float)perso.get_pourcent_PV()/100)*172;
	if(size < 0){
		size = 0;
	}
	if(who){
		// who = true donc joueur
		barre_hp.setFillColor(sf::Color(0,255,0));
		barre_hp.setPosition(sf::Vector2f(110.f, 32.f));
		barre_hp.setSize(sf::Vector2f(size, 22.f));
	}else{
		// who = false donc ennemi
		barre_hp.setFillColor(sf::Color(0,255,0));
		barre_hp.setPosition(sf::Vector2f(900.f, 32.f));
		barre_hp.setSize(sf::Vector2f(size, 22.f));
	}
	return barre_hp;
}
