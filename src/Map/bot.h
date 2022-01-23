/**
 * @file bot.h
 * @author Pierre-Louis Lagunegrand
 * @brief Describe bot behaviour and game difficulty
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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
#define TOT_POSSIBLE_SPOTS 862 // Possible spots where a bot can spawn.


/**
 * @brief Class to setup every bot in the map, initialize it with the bot difficulty
 * 
 * A bot location is defined by a "20" and a walkable area for a bot by a "21", it walks in a straight line 
 * 
 */
class bot
{
	int checknearby(sf::Vector2f coords);
	void initpositions();
private:
	int difficulty;
	int bot_number;
	int current;
	std::vector<fighter*> bots;
public:
	bot(int difficulty);
	fighter* current_bot(){return bots[current];}
	void rm_bot(){bots[current]->alive = false;}
	void print();
	void draw(sf::RenderWindow &win);
	int check_and_follow(sf::Vector2f coords);

	~bot();
};

