#include "combat.h"

void aff_background(sf::RenderWindow *window)
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("images/bacgroundcombattemp.png");
	sf::Sprite background(backgroundTexture);
	// sf::Vector2u size = backgroundTexture.getSize();
	// background.setOrigin(size.x/2, size.y/2);
	window->draw(background);
}

void aff_hp(sf::RenderWindow *window)
{
	// Affichage de la barre d'hp du personnage
	sf::Texture hppersoTexture;
	hppersoTexture.loadFromFile("images/hpbar.png");
	sf::Sprite hpperso(hppersoTexture);
	// sf::Vector2u Position(/* x= */ 500, /* y= */ 500);
	// hpperso.setOrigin(Position.x, Position.y);
	window->draw(hpperso);

	// Affichage de la barre d'hp de l'ennemi
}

void aff_background_hp(sf::RenderWindow *window, sf::Sprite *hp1, sf::Sprite *hp2, sf::Sprite *Background)
{
	window->draw(*Background);
	sf::Vector2f();
	//hp1->setOrigin();
}

void StartCombatMsgThread(sf::RenderWindow *window)
{
	sf::Thread thread(std::bind(&aff_combat, window));
	thread.launch();
}

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