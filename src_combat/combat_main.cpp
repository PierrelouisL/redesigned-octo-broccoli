#include "combat.h"

//#define DEBUG // A commenter pour enlever les commentaires

// Flags for key pressed
bool upFlag = false;
bool downFlag = false;
bool leftFlag = false;
bool rightFlag = false;
bool returnFlag = false;
bool actionFlag = false; // Si une action est en cours on ne gere plus les evenements!

sf::Font NiceFont;

void aff_combat(sf::RenderWindow *window, classetest* joueur, classetest* ennemi)
{
	static sf::Uint8 R = 255, G = 0, B = 0, A = 250;
	static char last_pressed = UP, blinking_way = 1;
	static int last_pos = 0;
	static sf::RectangleShape Battle_outline(sf::Vector2f(1142.f, 200.f));
	static sf::Text Atq[4];
	srand(time(0));
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

	// aff_background(window);
	// aff_hp(window);
	window->draw(Battle_outline);
	for (int i = 0; i < 4; i++)
	{
		if (i != last_pos)
		{
			Atq[i].setFont(NiceFont);
			Atq[i].setString(joueur->get_atq(i));
			Atq[i].setCharacterSize(40);
			Atq[i].setFillColor(sf::Color(R, G, B, 255));
			window->draw(Atq[i]);
		}
	}
	if (/*!actionFlag*/ 1)
	{
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
			if(!actionFlag){
				actionFlag = 1;
				ennemi->subit_atq(joueur->get_dmg_atq(last_pos));
				std::cout << ennemi->get_PV() << " " << std::endl;
				joueur->subit_atq(ennemi->get_dmg_atq((int)rand()%4));
				std::cout << joueur->get_PV() << std::endl;
			}
		}
	}

	// On fait clignotter le texte!
	blink(&A, &blinking_way);

#ifdef DEBUG
	std::cout << " last_pos= " << (int)last_pos << " A= " << (int)A << " last_pressed= " << (int)last_pressed << std::endl;
#endif
	Atq[last_pos].setFont(NiceFont);
	Atq[last_pos].setString(joueur->get_atq(last_pos));
	Atq[last_pos].setCharacterSize(40);
	Atq[last_pos].setFillColor(sf::Color(R, G, B, A));
	window->draw(aff_hp(window, *joueur, true));
	window->draw(aff_hp(window, *ennemi, false));
	//window->draw(aff_hp(window, *ennemi, false));
	window->draw(Atq[last_pos]);
	//window->display();
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
			actionFlag = false;
			break;
		default:
			break;
		}
	}

	/*if (event.type == sf::Event::MouseButtonReleased)
	{
		std::cout << "x=" << event.mouseButton.x << "y=" << event.mouseButton.y << std::endl;
	}*/
	return 0;
}

int main(int argc, char *argv[])
{
	sf::RenderWindow* window = new sf::RenderWindow;
	window->create(sf::VideoMode(1152, 704),
						"Petage de gueule en regle des pollueurs");
	NiceFont.loadFromFile("images/SourceSansPro-Regular.otf");

	// Allocation des textures -> Background, texte, hp
	// Allocation background
	sf::Texture *Background = new sf::Texture;
	Background->loadFromFile("images/bacgroundcombattemp.png");
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
	sf::Event *event = new sf::Event;

	// Creation des classes joueur et ennemi
	classetest joueur, ennemi;

	sf::Text nom_joueur(sf::String("Joueur"), NiceFont, 20);
	nom_joueur.setPosition(sf::Vector2f(120.f, 10.f));

	sf::Text Pollueur(sf::String("Pollueur"), NiceFont, 20);
	nom_joueur.setPosition(sf::Vector2f(120.f, 10.f));

	while (1)
	{
		// on gère les évènements
		while (window->pollEvent(*event))
		{
			if (handleEvents(*event))
			{
				window->close();
				std::cout << "goodbye!" << std::endl;
				return 0;
			}
		}
		// ScreenMutex.unlock();
		// TODO: Gérer tout ça dans une fonction plus tard...
		window->clear();
		window->draw(*Background_sprite);
		aff_combat(window, &joueur, &ennemi);
		window->draw(*Hp_Sprite);
		window->draw(*Hp2_Sprite);
		window->draw(nom_joueur);
		window->draw(Pollueur);
		window->display();
	}

	free(Background);
	free(Background_sprite);
	free(Hp);
	free(Hp_Sprite);
	free(Hp2_Sprite);
	return 0;
}
