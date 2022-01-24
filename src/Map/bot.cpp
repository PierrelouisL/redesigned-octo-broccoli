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

/**
 * @brief Construct a new bot::bot object but Difficulty not yet implemented
 * 
 * @param difficulty 
 */
bot::bot(int difficulty):difficulty(difficulty)
{
	// For every bot we try to find a appropriate location!
	//std::cout << "chances to spawn = " << spawn << std::endl;
	for(int y = 0; y < 61; ++y){
		for(int x = 1; x < 60; ++x){
			if(obstacle_ville1[x][y] == 8){
				// We are in a spot for a bot so we should make one spawn!
				bots.push_back(new fighter(1)); // 1 because bot
				bots[bots.size()-1]->change_char("Routier");
				bots[bots.size()-1]->load_character();
				bots[bots.size()-1]->init_coord(sf::Vector2f(y*64, x*64)+sf::Vector2f(-32, -80));
				bots[bots.size()-1]->setPosition(sf::Vector2f(y*64, x*64)+sf::Vector2f(-32, -80));
				std::cout << "actually spawned x ; y " << bots[bots.size()-1]->getPosition().x << " ; " << bots[bots.size()-1]->getPosition().y << std::endl;
			}
			if(obstacle_ville1[x][y] == 9){
				// The boss AKA Trump!
				bots.push_back(new fighter(2)); // 2 because boss
				bots[bots.size()-1]->change_char("Routier");
				bots[bots.size()-1]->load_character();
				bots[bots.size()-1]->init_coord(sf::Vector2f(y*64, x*64)+sf::Vector2f(-32, -80));
				bots[bots.size()-1]->setPosition(sf::Vector2f(y*64, x*64)+sf::Vector2f(-32, -80));
				std::cout << "actually spawned x ; y " << bots[bots.size()-1]->getPosition().x << " ; " << bots[bots.size()-1]->getPosition().y << std::endl;
			} 
		}
	}
}

bot::~bot()
{
	for(unsigned int i = 0; i < bots.size(); ++i){
		free(bots[i]);
	}
}

/**
 * @brief draws every bot on the window 
 * 
 * @param win 
 */
void bot::draw(sf::RenderWindow &win){
	//std::cout << "printing" << std::endl;
	for(unsigned int i = 0; i < bots.size(); ++i){
		win.draw(*bots[i]);
		//std::cout << perso.getPosition().x << " " << bots[i]->getPosition().x << std::endl;
	}
}


/**
 * @brief Prints every bot to debug
 * 
 */
void bot::print(){
	std::cout << "printing every bot..." << std::endl;
	for(unsigned int i =0; i < bots.size(); ++i){
		std::cout << "Bot nb "<< i<< " x="<<bots[i]->getPosition().x << " y=" << bots[i]->getPosition().y << " HP=" << bots[i]->get_PV() << std::endl;
	}
}

/**
 * @brief Function to tell which bot is located near this coords (actualize current_bot())
 * 
 * @param coords 
 */
void bot::which_bot(sf::Vector2f coords){
	coords - sf::Vector2f(-32, -80);
	int index = 0;
	for(auto& bot: bots){
		std::cout << "position x= " << coords.x << " botx = " << bot->getPosition().x <<" position y=" << coords.y  <<" boty = " << bot->getPosition().y<< std::endl;
		if((bot->getPosition().x + 200) > coords.x && (bot->getPosition().x-200) < coords.x){
			if((bot->getPosition().y + 200) > coords.y && (bot->getPosition().y-200)< coords.y){
				std::cout << "near bot index = " << index << std::endl;
				current = index;
				return;
			}
		}
		index++;
	}
}