#include "Character.h"
#include "Obstacle.h"
#include <wait.h>
#include "bot.h"

// Pour avoir une vraie fonction random
#include "random.hpp"
using Random = effolkronium::random_static;

#define MOVESPEED 10

TileCharacter::TileCharacter(const TileCharacter& T){
	this->setPosition(T.getPosition());
	this->setOrigin(T.getOrigin());
	this->setRotation(T.getRotation());
	this->setScale(T.getScale());
	_character = T._character;
	_eye = T._eye;
	_feet_topleft = T._feet_topleft;
	_feet_topright = T._feet_topright;
	_feet_bottomleft = T._feet_bottomleft;
	_feet_bottomright = T._feet_bottomright;
	_upFlag = T._upFlag;
	_downFlag = T._downFlag;
	_rightFlag = T._rightFlag;
	_leftFlag = T._leftFlag;
	_is_main_character = T._is_main_character;
}

void TileCharacter::load_character(){

	TileCharacter perso(_character);

	// on définit le niveau à l'aide de numéro de tuiles
	int level[] = { 0, 1, 8, 9 };

    switch(_eye){
    	case Face:
    		break;
    	case Back:
    		level[0] += 2;	level[1] +=	2;
    		level[2] += 2;	level[3] += 2;
    		break;
    	case Left:
    		level[0] += 4;	level[1] += 4;
    		level[2] += 4;	level[3] += 4; 
    		break;
    	case Right:
    		level[0] += 6;	level[1] += 6;
    		level[2] += 6;	level[3] += 6;
    		break;
    	default:
    		break;
    }

   	std::string pathCharacter = "images/Personnage/" + _character + ".png";
	if(!this->load(pathCharacter, level, 2, 2)){
		std::cout << "Erreur du chargement du personnage" << std::endl;
	}
}


void TileCharacter::init_coord(sf::View &view){ // If main character
		_feet_bottomleft 	= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +64));	//
		_feet_bottomright	= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +64));	// Save the coord of each
		_feet_topleft		= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +32));	// coord of character's feet
		_feet_topright		= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +32));	//
}

void TileCharacter::init_coord(sf::Vector2f coords){ // If bot
		_feet_bottomleft 	= sf::Vector2f(coords + sf::Vector2f(-32, +64));	//
		_feet_bottomright	= sf::Vector2f(coords + sf::Vector2f(+32, +64));	// Save the coord of each
		_feet_topleft		= sf::Vector2f(coords + sf::Vector2f(-32, +32));	// coord of character's feet
		_feet_topright		= sf::Vector2f(coords + sf::Vector2f(+32, +32));	//
}


sf::Vector2f TileCharacter::checkFrontCase(int val){

	sf::Vector2f next_case1;
	sf::Vector2f next_case2;

	switch(_eye){
		case Left:
			next_case1 = _feet_topleft + sf::Vector2f(-8, 0);
			next_case2 = _feet_bottomleft + sf::Vector2f(-8, 0);
			break;
		case Right:
			next_case1 = _feet_topright + sf::Vector2f(8, 0);
			next_case2 = _feet_bottomright + sf::Vector2f(8, 0);
			break;
		case Back:
			next_case1 = _feet_topright + sf::Vector2f(0, -16);
			next_case2 = _feet_topleft + sf::Vector2f(0, -16);
			break;
		case Face:
			next_case1 = _feet_bottomright + sf::Vector2f(0, 16);
			next_case2 = _feet_bottomleft + sf::Vector2f(0, 16);   		
			break;
		default:
			break;
	}

	next_case1 = next_case1 + next_case2;
	next_case1 = next_case1/2.f;

	if(obstacle_ville1[ abs((int) ((next_case1.y)/64)) ][ abs((int) (next_case1.x/64)) ] == val){
		return next_case1;
	}
	else{
		return sf::Vector2f(-1, -1);	// Aucune case
	}
}

void TileCharacter::checkKeyMove(sf::Event &event){
        
    // Si on appuit sur une touche
    if (event.type == sf::Event::KeyPressed){
        switch (event.key.code){
            case sf::Keyboard::Up :     _upFlag		= true; break;
            case sf::Keyboard::Down:    _downFlag	= true; break;
            case sf::Keyboard::Left:    _leftFlag	= true; break;
            case sf::Keyboard::Right:   _rightFlag	= true; break;
            default : break;
        }
    }

    // Si on relache la touche
    if (event.type == sf::Event::KeyReleased){
        switch (event.key.code){
            // Process the up, down, left and right keys
            case sf::Keyboard::Up :     _upFlag    	= false; break;
            case sf::Keyboard::Down:    _downFlag  	= false; break;
            case sf::Keyboard::Left:    _leftFlag  	= false; break;
            case sf::Keyboard::Right:   _rightFlag	= false; break;
            default : break;
        }
    }
}

void TileCharacter::move(sf::View &view){
	  
	sf::Vector2f next_case;

	if(_leftFlag){  // left key is pressed: move our character
		
		_eye = Left;
		next_case = checkFrontCase(0);
		if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle	
			view.move(-MOVESPEED, 0);
		}       
    }
    else if(_rightFlag){  // right key is pressed: move our character
    	
    	_eye = Right;
    	next_case = checkFrontCase(0);
    	if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle
       		view.move(MOVESPEED, 0);
       	}
    }
    else if(_upFlag){     // up key is pressed: move our character
		
		_eye = Back;
		next_case = checkFrontCase(0);
		if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle
        	view.move(0, -MOVESPEED);
    	}
    }
    else if(_downFlag){   // down key is pressed: move our character
		_eye = Face; 
		next_case = checkFrontCase(0);
    	if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle
        	view.move(0, MOVESPEED);
    	}           
    }

    this->load_character();

    _feet_bottomleft 	= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +64));	//
    _feet_bottomright	= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +64));	// Save the coord of each
    _feet_topleft		= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +32));	// coord of character's feet
	_feet_topright		= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +32));	//
}

void TileCharacter::actionKey(sf::Event &event, TileElement &element, bool* heal){
	
	if(event.type == sf::Event::KeyPressed){

		if(event.key.code == sf::Keyboard::A){
	        sf::Vector2f next_case = checkFrontCase(4);

	    	if( next_case != sf::Vector2f(-1, -1) ){
	    		
	    		obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = -1;

				TileMap temp_element;
	    		int level[] = { 0, 1 };
	    		
				if(!temp_element.load("images/arbre.png", level, 1, 2)){
					std::cout << "Erreur du chargement de l'élément" << std::endl;
				}

				// We heal the player if he plants a tree!
				std::cout << "healing!" << std::endl;
				*heal = true;

				temp_element.setPosition(sf::Vector2f((int) (next_case.x/64)*64, (int) ((next_case.y)/64)*64) + sf::Vector2f(-2, -80)); 		
				element.put_VectorElement(temp_element);
				element.put_VectorType(2);
	    	}else{
				*heal=false;
			}
	    }

	    if(oneMoveFlag()){
	    	sf::Vector2f next_case = checkFrontCase(5);
	    	
	    	if( next_case != sf::Vector2f(-1, -1) ){

	    		obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = 0;

				TileMap temp_element;
	    		int level[] = { 0, 1, 2, 3};
	    		
				if(!temp_element.load("images/voiture.png", level, 2, 2)){
					std::cout << "Erreur du chargement de l'élément voiture" << std::endl;
				}

				temp_element.setPosition(sf::Vector2f((int) (next_case.x/64)*64, (int) ((next_case.y)/64)*64) + sf::Vector2f(640, -64)); 		
				element.put_VectorElement(temp_element);
				element.put_VectorType(3);
	    	}
	    }
    } 
}


/**
 * @brief We'll init every positions using the bot_number, bot_difficulty and the obstacle array
 * 
 */
void bot::initpositions(){
	//obstacle_ville1;
	std::vector<sf::Vector2f> locations;
	float spawn = (float)this->bot_number/TOT_POSSIBLE_SPOTS;
	sf::View pos;
	int nb_spawned = 0;
	// For every bot we try to find a appropriate location!
	//auto val = Random::get<bool>( 0.7 ) // 70% to generate true

	//std::cout << "chances to spawn = " << spawn << std::endl;
	for(int y = 0; y < 59; ++y){
		for(int x = 0; x < 39; ++x){
			if(obstacle_ville1[x][y] == 8){
				// We are in a spot for a bot so we should make one spawn!
				nb_spawned++;
				std::cout << "a bot spawned! pos=" << x*64 << " y= " << y*64 <<" nb = " << nb_spawned << "obstc=" << obstacle_ville1[x][y]<< std::endl;
				//bots.insert(bots.end(), new TileCharacter());
				bots.push_back(new fighter);
				bots[nb_spawned]->change_char("Gretta");
				bots[nb_spawned]->load_character();
				bots[nb_spawned]->init_coord(sf::Vector2f(y*64, x*64));
				bots[nb_spawned]->setPosition(sf::Vector2f(y*64, x*64));
			}
		}
	}
	this->bot_number = nb_spawned;
}
