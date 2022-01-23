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

#include "fight_scene.h"

#define DEBUG // A commenter pour enlever les commentaires

typedef enum{MENU, CITY, FIGHT, END}States;

extern sf::Mutex WinMutex; // We ensure that we finished drawing before drawing in another thread!
extern sf::Mutex Console; // We ensure that we finished drawing before drawing in another thread!
extern Gamemode g_mode;

/* Miscs */

void printf_s(std::string msg){
    Console.lock();
    std::cout << msg << std::endl;
    Console.unlock();
}

void fight_scene::blink(sf::Uint8 *A, char *blinking_way)
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

void fight_scene::flagHandler(char flag, int *last_pos, std::vector<sf::Text*> Atq, sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, char last_pressed)
{
	#ifdef DEBUG
	std::cout << (int)flag << "=f" << std::endl;
	#endif
	if (flag == UP)
	{ // Up
		Atq[*last_pos]->setFillColor(sf::Color(R, G, B, 255));
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
		Atq[*last_pos]->setFillColor(sf::Color(R, G, B, 255));
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
		Atq[*last_pos]->setFillColor(sf::Color(R, G, B, 255));
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
		Atq[*last_pos]->setFillColor(sf::Color(R, G, B, 255));
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
sf::RectangleShape fight_scene::aff_hp(sf::RenderWindow* window, fighter perso, bool who){
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

void fight_scene::goodbye(){
	upFlag = false;
	downFlag = false;
	leftFlag = false;
	rightFlag = false;
	returnFlag = false;
	actionFlag = NOTHING;
}



int fight_scene::aff_combat(sf::RenderWindow *window, fighter* joueur, fighter* ennemi, std::vector<sf::Text*> Atq)
{
	static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
	sf::Font Font;
	Font.loadFromFile("images/SourceSansPro-Regular.otf");
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
	}


#ifdef DEBUG
	std::cout << "up = " << upFlag << "down = " << downFlag << "right" << rightFlag << "left=" << leftFlag << std::endl;
#endif

	for (int i = 0; i < 4; i++)
	{
		if ((i != last_pos) && actionFlag == NOTHING)
		{
			Atq[i]->setString(joueur->get_atk(i));
			Atq[i]->setFillColor(sf::Color(R, G, B, 255));
			window->draw(*Atq[i]);
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
	Atq[last_pos]->setString(joueur->get_atk(last_pos));
	Atq[last_pos]->setFillColor(sf::Color(R, G, B, A));
	window->draw(aff_hp(window, *joueur, true));
	window->draw(aff_hp(window, *ennemi, false));
	switch(actionFlag){
		case NOTHING:
			#ifdef DEBUG
			std::cout << "--->draw atq" << std::endl;
			#endif
			window->draw(*Atq[last_pos]);
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

int fight_scene::handleEvents(sf::Event event)
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


void fight_scene::Display(sf::RenderWindow& window, fighter* player, fighter* currentbot){

	window.setActive(true);
	window.clear();
	window.setView(window.getDefaultView());
	window.draw(*Background_sprite);
	if(aff_combat(&window, player, currentbot, Atq) < 0){
		sf::Clock clk_fin;
		sf::RectangleShape HideMes(sf::Vector2f(1142.f, 200.f));
		HideMes.setFillColor(sf::Color(200, 226, 226, 255));
		HideMes.setPosition(sf::Vector2f(5.f, 499.f));
		window.draw(HideMes);
		if(player->get_PV() < 0){
			std::cout << "le joueur est mort" << std::endl;
			player->aff_fin(&window, VICTOIRE); // A remplacer  plus tard
		}else{
			std::cout << "Le pollueur est mort bien vu" << std::endl;
			currentbot->aff_fin(&window, DEFAITE);
		}
		window.display();
		while(clk_fin.getElapsedTime().asSeconds() > 5); // Petit délai de 10s
		goodbye();
		g_mode = normal;
		currentbot->alive = false;
		return;
		// On passe à l'état city et on attend qu'on revienne pour repartir!
	}

	window.draw(*Hp_Sprite);
	window.draw(*Hp2_Sprite);
	window.draw(*nom_joueur);
	window.draw(*nom_joueur);
	window.display();
	window.setActive(false);
}


fight_scene::~fight_scene()
{
	delete Background;
	delete Background_sprite;
	delete Hp;
	delete Hp2_Sprite;
	delete Hp_Sprite;
	delete nom_pollueur;
	delete nom_joueur;
	for(int i = 0; i< 4; ++i){
        delete Atq[i];
    }
}

fight_scene::fight_scene()
{
	NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");
	Background = new sf::Texture;
	Background->loadFromFile("images/background_combat_ville.png");
	Background_sprite = new sf::Sprite;
	Background_sprite->setTexture(*Background);

	// Allocation HP1
	Hp = new sf::Texture;
	Hp->loadFromFile("images/hpbar.png");
	Hp_Sprite = new sf::Sprite;
	Hp_Sprite->setTexture(*Hp);
	Hp_Sprite->setPosition(sf::Vector2f(50.f, 0.f));

	// Allocation HP2
	Hp2_Sprite = new sf::Sprite;
	Hp2_Sprite->setTexture(*Hp);
	Hp2_Sprite->setPosition(sf::Vector2f(840.f, 0.f));

	nom_joueur = new sf::Text;
	nom_joueur->setFont(NiceFont);
	nom_joueur->setCharacterSize(20);
	nom_joueur->setString(sf::String("Joueur"));
	nom_joueur->setPosition(sf::Vector2f(120.f, 10.f));

	nom_pollueur = new sf::Text;
	nom_pollueur->setFont(NiceFont);
	nom_pollueur->setCharacterSize(20);
	nom_pollueur->setString(sf::String("Pollueur"));
	nom_pollueur->setPosition(sf::Vector2f(910.f, 10.f));

    for(int i = 0; i< 4; ++i){
        Atq.push_back(new sf::Text);
        Atq[i]->setFont(NiceFont);
        Atq[i]->setCharacterSize(40);
    }
    Atq[0]->setPosition(sf::Vector2f(20.f, 510.f));
    Atq[1]->setPosition(sf::Vector2f(600.f, 510.f));
    Atq[2]->setPosition(sf::Vector2f(20.f, 610.f));
    Atq[3]->setPosition(sf::Vector2f(600.f, 610.f));
}