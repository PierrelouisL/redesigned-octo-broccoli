/**
 * @file fighter.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "fighter.h"

#define DEBUG // A commenter pour enlever les commentaires


/* Miscs */

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
sf::RectangleShape aff_hp(sf::RenderWindow* window, fighter perso, bool who){
	sf::RectangleShape barre_hp(sf::Vector2f(172.f,22.f)); // Ce qui sera en vert pour afficher ce qu'il reste d'hp au perso
	//int PV = perso.get_PV();
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

/* Fighter class */

// Flags for key pressed
bool upFlag = false;
bool downFlag = false;
bool leftFlag = false;
bool rightFlag = false;
bool returnFlag = false;
char actionFlag = NOTHING; // Si une action est en cours on ne gere plus les evenements!


void goodbye(sf::Texture *Background, sf::Sprite *Background_sprite, sf::Texture *Hp, sf::Sprite *Hp_Sprite, sf::Sprite *Hp2_Sprite, sf::Event *event){
	upFlag = false;
	downFlag = false;
	leftFlag = false;
	rightFlag = false;
	returnFlag = false;
	actionFlag = NOTHING;
	delete Background;
	delete Background_sprite;
	delete Hp;
	delete Hp_Sprite;
	delete Hp2_Sprite;
	delete event;
}


sf::Font NiceFont;
sf::Text Atq[4];


int aff_combat(sf::RenderWindow *window, fighter* joueur, fighter* ennemi)
{
	static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
	static char last_pressed = UP, blinking_way = 1;
	static int last_pos = 0;
	static sf::RectangleShape Battle_outline(sf::Vector2f(1142.f, 200.f));
	static sf::Clock clk;
	static int last_atq_ennemi; // Permet de stoquer -1 si c'est la premiere fois que l'ennemi atq (donc doit faire des degats) ou alors dire la derniere attaque
	srand(time(0));

	// On gère ici le temps écoulé depuis l'action pour durer TEMPO_MESS (afficher le message pendant 3s) 
	if(clk.getElapsedTime().asSeconds() > TEMPO_MESS){
		if(actionFlag == MES_PLAYER){
			clk.restart();
			actionFlag = MES_ENNEMY;
		}else if(actionFlag == MES_ENNEMY){
			actionFlag = NOTHING;
		}
	}
	if (R == 255)
	{
		R = 254;
		// On positionne les formes ici
		Battle_outline.setFillColor(sf::Color(255, 255, 255, 100));
		Battle_outline.setOutlineThickness(5.f);
		Battle_outline.setOutlineColor(sf::Color(sf::Color::Red));
		Battle_outline.setPosition(sf::Vector2f(5.f, 499.f));
		Atq[0].setPosition(sf::Vector2f(20.f, 510.f));
		Atq[1].setPosition(sf::Vector2f(600.f, 510.f));
		Atq[2].setPosition(sf::Vector2f(20.f, 610.f));
		Atq[3].setPosition(sf::Vector2f(600.f, 610.f));
	}


#ifdef DEBUG
	std::cout << "up = " << upFlag << "down = " << downFlag << "right" << rightFlag << "left=" << leftFlag << std::endl;
#endif

	for (int i = 0; i < 4; i++)
	{
		if ((i != last_pos) && actionFlag == NOTHING)
		{
			Atq[i].setFont(NiceFont);
			Atq[i].setString(joueur->get_atk(i));
			Atq[i].setCharacterSize(40);
			Atq[i].setFillColor(sf::Color(R, G, B, 255));
			window->draw(Atq[i]);
			std::string s = joueur->get_atk(i);
			std::cout << "----------printing atq " << i << "string =" << s << std::endl;
		}
	}
	std::cout << "x win= "<< window->getView().getCenter().x << " y win = " << window->getView().getCenter().y << "comparé à 500 500" << std::endl;

	if (upFlag)
	{
		flagHandler(UP, &last_pos, Atq, R, G, B, last_pressed);
	}
	else if (downFlag)
	{
		flagHandler(DOWN, &last_pos, Atq, R, G, B, last_pressed);
	}
	else if (rightFlag)
	{
		flagHandler(RIGHT, &last_pos, Atq, R, G, B, last_pressed);
	}
	else if (leftFlag)
	{
		flagHandler(LEFT, &last_pos, Atq, R, G, B, last_pressed);
	}
	else if (returnFlag)
	{
		if(actionFlag == NOTHING){
			actionFlag = MES_PLAYER;
			ennemi->subit_atq(joueur->get_dmg_atq(last_pos));
			std::cout << "Ennemi PV= " <<ennemi->get_PV() << " " << std::endl;
			clk.restart();
		}
	}

	// On fait clignotter le texte!
	blink(&A, &blinking_way);

#ifdef DEBUG
	std::cout << " last_pos= " << (int)last_pos << " A= " << (int)A << " last_pressed= " << (int)last_pressed << std::endl;
#endif
	Atq[last_pos].setFont(NiceFont);
	Atq[last_pos].setString(joueur->get_atk(last_pos));
	Atq[last_pos].setCharacterSize(40);
	Atq[last_pos].setFillColor(sf::Color(R, G, B, A));
	window->draw(aff_hp(window, *joueur, true));
	window->draw(aff_hp(window, *ennemi, false));
	switch(actionFlag){
		case NOTHING:
			#ifdef DEBUG
			std::cout << "--->draw atq" << std::endl;
			#endif
			window->draw(Atq[last_pos]);
			last_atq_ennemi = -1;
			break;
		case MES_PLAYER:
			joueur->aff_message(window, last_pos);
			last_atq_ennemi = -1;
			#ifdef DEBUG
			std::cout << "---->MES_PLAYER" << std::endl;
			#endif
			break;
		case MES_ENNEMY:
			if(last_atq_ennemi != -1){
				ennemi->aff_message(window, last_atq_ennemi);
				#ifdef DEBUG
				std::cout << "---->MES_ENNEMY" << std::endl;
				#endif
			}else{
				last_atq_ennemi = rand()%4;
				joueur->subit_atq(ennemi->get_dmg_atq(last_atq_ennemi));
				#ifdef DEBUG
				std::cout << "----->ennemi atq = " << last_atq_ennemi << std::endl;
				#endif
				ennemi->aff_message(window, last_atq_ennemi);
			}
			break;
	}
	if(joueur->get_PV() <= 0 || ennemi->get_PV() <= 0)
		return -1;
	return 0;
}

int handleEvents(sf::Event event)
{
	if (event.type == sf::Event::Closed){
		return 1;
	}
	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			upFlag = true;
			break;
		case sf::Keyboard::Down:
			downFlag = true;
			break;
		case sf::Keyboard::Left:
			leftFlag = true;
			break;
		case sf::Keyboard::Right:
			rightFlag = true;
			break;
		case sf::Keyboard::Return:
			returnFlag = true;
			break;
		case sf::Keyboard::Escape:
			return 1;
		default:
			break;
		}
	}

	// Si on relache la touche
	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		// Process the up, down, left and right keys
		case sf::Keyboard::Up:
			upFlag = false;
			break;
		case sf::Keyboard::Down:
			downFlag = false;
			break;
		case sf::Keyboard::Left:
			leftFlag = false;
			break;
		case sf::Keyboard::Right:
			rightFlag = false;
			break;
		case sf::Keyboard::Return:
			returnFlag = false;
			//actionFlag = false;
			break;
		default:
			break;
		}
	}
	return 0;
}

int fight_scene(sf::RenderWindow* window, fighter* joueur, fighter* ennemi)
{
	std::cout << "fight engaged!" << std::endl;
	NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");


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

	// Allocations events
	//sf::Event event;
	sf::Event *event = new sf::Event;

	// Creation des classes joueur et ennemi
	//fighter joueur, ennemi;

	sf::Text nom_joueur(sf::String("Joueur"), NiceFont, 20);
	nom_joueur.setPosition(sf::Vector2f(120.f, 10.f));
	sf::Text Pollueur(sf::String("Pollueur"), NiceFont, 20);
	Pollueur.setPosition(sf::Vector2f(910.f, 10.f));


	while (1)
	{
		#ifndef DEBUG
		std::cout << "|" << std::endl;
		#endif
		// on gère les évènements
		while (window->pollEvent(*event))
		{
			if (handleEvents(*event))
			{
				window->close();
				std::cout << "goodbye!" << std::endl;
				goodbye(Background, Background_sprite, Hp, Hp_Sprite, Hp2_Sprite, event);
				exit(0);
			}
		}
		// TODO: Gérer tout ça dans une fonction plus tard...
		window->clear();
		window->setView(window->getDefaultView());
		window->draw(*Background_sprite);
		if(aff_combat(window, joueur, ennemi) < 0){
			sf::Clock clk_fin;
			sf::RectangleShape HideMes(sf::Vector2f(1142.f, 200.f));
			HideMes.setFillColor(sf::Color(200, 226, 226, 255));
			HideMes.setPosition(sf::Vector2f(5.f, 499.f));
			window->draw(HideMes);
			if(joueur->get_PV() < 0){
				std::cout << "le joueur est mort" << std::endl;
				joueur->aff_fin(window, VICTOIRE); // A remplacer  plus tard
			}else{
				std::cout << "Le pollueur est mort bien vu" << std::endl;
				ennemi->aff_fin(window, DEFAITE);
			}
			window->display();
			while(clk_fin.getElapsedTime().asSeconds() < 1); // Petit délai de 10s
			goodbye(Background, Background_sprite, Hp, Hp_Sprite, Hp2_Sprite, event);
			return 0 ;
		}
		#ifdef DEBUG
		std::cout <<"drawing.."<< std::endl;
		#endif
		window->draw(*Hp_Sprite);
		window->draw(*Hp2_Sprite);
		window->draw(nom_joueur);
		window->draw(Pollueur);
		window->display();
	}

	goodbye(Background, Background_sprite, Hp, Hp_Sprite, Hp2_Sprite, event);
	return 0;
}
