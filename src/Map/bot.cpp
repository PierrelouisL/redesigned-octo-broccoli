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

extern int obstacle_ville1[61][60];
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
		bots.push_back(new fighter());
		//bots.insert(bots.end(), new fighter());
	}
	initpositions();
}

bot::~bot()
{
	for(int i = 0; i < this->bot_number; ++i){
		free(bots[i]);
	}
}
/**
 * @brief 
 * 
 * @param win 
 */
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
/*int bot::checknearby(sf::Vector2f coords){
	// We first check if we have a player nearby any of all the bots!
	float xbot = 0, ybot = 0;
	for(int nb_bot = 1; nb_bot < this->bot_number ; ++nb_bot){
		xbot = bots[nb_bot]->getPosition().x;
		ybot = bots[nb_bot]->getPosition().y;
		//std::cout << "coords bot " << nb_bot << " x=" << xbot << " y=" << ybot << "coords perso x=" << coords.x << " y=" << coords.y << std::endl;
		if((xbot + 20) > coords.x && (xbot-20) < coords.x){
			if((ybot + 20) > coords.y && (ybot-20)< coords.y){
				//std::cout << "player nearby! x = "<< xbot << " y = " << ybot << "nb_bot" << nb_bot<< std::endl;
				current = nb_bot;
				return nb_bot;
			}
			//current = nb_bot;
			//return nb_bot;
		}
	}
	return -1;

}*/



/**
 * @brief Prints every bot to debug
 * 
 */
void bot::print(){
	std::cout << "printing every bot..." << std::endl;
	for(int i =0; i < bot_number; ++i){
		std::cout << "Bot nb "<< i<< " x="<<bots[i]->getPosition().x << " y=" << bots[i]->getPosition().y << " HP=" << bots[i]->get_PV() << std::endl;
	}
}

/**
 * @brief Checks if player is nearby then follows him to battle
 * 
 * @param player
 */
/*int bot::check_and_follow(sf::Vector2f coords){
	print();
	checknearby(coords);
	if(this->current <= 0){
		//std::cout << "not found!" << std::endl;
		return this->current;
	}

	return this->current;
	// We first check where should we be heading to follow him
	if(player.getPosition().x < this->bots[this->current]->getPosition().x){
		// player coord x < bot coord x so we should decrease x
		std::cout << "decreasing x... xplayer= " <<  player.getPosition().x << " xbot= " << this->bots[this->current]->getPosition().x << std::endl;
		//this->bots[this->current]->move
	}else if(player.getPosition().x > this->bots[this->current]->getPosition().x){
		// player coord x > bot coord x so we should increase x
		std::cout << "increasing x... xplayer= " <<  player.getPosition().x << " xbot= " << this->bots[this->current]->getPosition().x << std::endl;
	}else{
		// player coord x = bot coord x so we check y now
		if(player.getPosition().y < this->bots[this->current]->getPosition().y){
			// player coord y < bot coord y so we should decrease y
			std::cout << "decreasing y... yplayer= " <<  player.getPosition().y << " ybot= " << this->bots[this->current]->getPosition().y << std::endl;
		}else if(player.getPosition().y > this->bots[this->current]->getPosition().y){
			// player coord y > bot coord y so we should increase y
			std::cout << "increasing y... yplayer= " <<  player.getPosition().y << " ybot= " << this->bots[this->current]->getPosition().y << std::endl;
		}else{
			// same spot so we launch COMBATTT
			std::cout << "FIGHT!" << std::endl;
		}
	}
}*/

/**
 * @brief We'll init every positions using the bot_number, bot_difficulty and the obstacle array
 * 
 */
void bot::initpositions(){
	//obstacle_ville1;
	std::vector<sf::Vector2f> locations;
	//float spawn = (float)this->bot_number/TOT_POSSIBLE_SPOTS;
	sf::View pos;
	int nb_spawned = 0;
	// For every bot we try to find a appropriate location!
	//auto val = Random::get<bool>( 0.7 ) // 70% to generate true

	//std::cout << "chances to spawn = " << spawn << std::endl;
	for(int y = 0; y < 59; ++y){
		for(int x = 1; x < 39; ++x){
			if(obstacle_ville1[x][y] == 8){
				// We are in a spot for a bot so we should make one spawn!
				nb_spawned++;
				std::cout << "a bot spawned! pos=" << x*64 << " y= " << y*64 <<" nb = " << nb_spawned << "obstc=" << obstacle_ville1[x][y]<< std::endl;
				//bots.insert(bots.end(), new TileCharacter());
				bots.push_back(new fighter);
				bots[nb_spawned]->change_char("Routier");
				bots[nb_spawned]->load_character();
				bots[nb_spawned]->init_coord(sf::Vector2f(y*64, x*64)+sf::Vector2f(-32, -80));
				bots[nb_spawned]->setPosition(sf::Vector2f(y*64, x*64)+sf::Vector2f(-32, -80));
			}
		}
	}
	this->bot_number = nb_spawned;
}