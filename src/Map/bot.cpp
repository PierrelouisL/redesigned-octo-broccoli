/**
 * @file bot.cpp
 * @author Pierre-Louis Lagunegrand
 * @brief 
 * @version 0.1
 * @date 2022-01-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "bot.h"
//#include "Obstacle.h"


bot::bot(int difficulty):difficulty(difficulty)
{
	switch(difficulty){
		case EASY:
			this->bot_number = EASY_BOT_NB;
			break;
		case MEDIUM:
			this->bot_number = MEDIUM_BOT_NB;
			break;
		case HARD:
			this->bot_number = HARD_BOT_NB;
			break;
	}
	for(int i = 0; i < this->bot_number; ++i){
		bots.insert(bots.end(), new TileCharacter());
	}
	initpositions();
}

bot::~bot()
{
	for(int i = 0; i < this->bot_number; ++i){
		free(bots[i]);
	}
}

void bot::draw(sf::RenderWindow &win){
	//std::cout << "printing" << std::endl;
	for(int i = 0; i < this->bot_number; ++i){
		win.draw(*bots[i]);
		//std::cout << perso.getPosition().x << " " << bots[i]->getPosition().x << std::endl;
	}
}

/**
 * @brief This function role is to check if we have a player nearby (5x5 square) and follow him to engage combat!
 * 
 * @param player 
 */
int bot::checknearby(TileCharacter player){
	// We first check if we have a player nearby any of all the bots!
	float xbot = 0, ybot = 0;
	for(int nb_bot = 0; nb_bot < this->bot_number ; ++nb_bot){
		xbot = bots[nb_bot]->getPosition().x;
		ybot = bots[nb_bot]->getPosition().y;
		if((xbot + 200) > player.getPosition().x && (xbot-200) < player.getPosition().x){
			if((ybot + 200) > player.getPosition().y && (ybot-200)< player.getPosition().y){
				std::cout << "player nearby! x = "<< xbot << " y = " << ybot << "nb_bot" << nb_bot<< std::endl;
				return nb_bot;
			}
		}
	}
	return -1;

	
}

/**
 * @brief Checks if player is nearby then follows him to battle
 * 
 * @param player
 */
void bot::check_and_follow(TileCharacter player){
	int bot_following_nb = checknearby(player);
	if(bot_following_nb < 0){
		return;
	}
	sf::View vieww(sf::Vector2f(this->bots[bot_following_nb]->getPosition().x, this->bots[bot_following_nb]->getPosition().y));
	std::cout << "player nearby nb= " << bot_following_nb << std::endl;
	// We first check where should we be heading to follow him
	if(player.getPosition().x < this->bots[bot_following_nb]->getPosition().x){
		// player coord x < bot coord x so we should decrease x
		std::cout << "decreasing x... xplayer= " <<  player.getPosition().x << " xbot= " << this->bots[bot_following_nb]->getPosition().x << std::endl;
		this->bots[bot_following_nb]->move
	}else if(player.getPosition().x > this->bots[bot_following_nb]->getPosition().x){
		// player coord x > bot coord x so we should increase x
		std::cout << "increasing x... xplayer= " <<  player.getPosition().x << " xbot= " << this->bots[bot_following_nb]->getPosition().x << std::endl;
	}else{
		// player coord x = bot coord x so we check y now
		if(player.getPosition().y < this->bots[bot_following_nb]->getPosition().y){
			// player coord y < bot coord y so we should decrease y
			std::cout << "decreasing y... yplayer= " <<  player.getPosition().y << " ybot= " << this->bots[bot_following_nb]->getPosition().y << std::endl;
		}else if(player.getPosition().y > this->bots[bot_following_nb]->getPosition().y){
			// player coord y > bot coord y so we should increase y
			std::cout << "increasing y... yplayer= " <<  player.getPosition().y << " ybot= " << this->bots[bot_following_nb]->getPosition().y << std::endl;
		}else{
			// same spot so we launch COMBATTT
			std::cout << "FIGHT!" << std::endl;
		}
	}
}