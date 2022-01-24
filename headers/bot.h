#pragma once
#include "Window.h"
#include "Character.h"
#include "fighter.h"

#define EASY 0
#define MEDIUM 1
#define HARD 2
#define EASY_BOT_NB 5
#define MEDIUM_BOT_NB 10
#define HARD_BOT_NB 15


/**
 * @brief Class to setup every bot in the map, initialize it with the bot difficulty
 * 
 * A bot location is defined by a "8" or "9" for Trump
 * 
 */
class bot
{
private:
	int difficulty;
	int current;
	std::vector<fighter*> bots;
public:
	bot(int difficulty);
	fighter* current_bot(){return bots[current];}
	void rm_bot(){bots[current]->alive = false;}
	void print();
	void draw(sf::RenderWindow &win);
	void which_bot(sf::Vector2f coords);

	~bot();
};

