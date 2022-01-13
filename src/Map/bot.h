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
 */
class bot
{
	int checknearby(TileCharacter player);
	void initpositions();
private:
	int difficulty;
	int bot_number;
	std::vector<TileCharacter*> bots;
public:
	bot(int difficulty);
	void draw(sf::RenderWindow &win);
	void check_and_follow(TileCharacter player);
	~bot();
};

