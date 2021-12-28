#include "Window.h"
#include "Character.h"
#include "Obstacle.h"

#define MOVESPEED 10

TileCharacter TileCharacter::load_character(const orientation &orientation){

	TileCharacter perso(_character);

	// on définit le niveau à l'aide de numéro de tuiles
	int level[] = { 0, 1, 8, 9 };

    switch(orientation){
    	case Face:
    		break;
    	case Back :
    		level[0] += 2;	level[1] +=	2;
    		level[2] += 2;	level[3] += 2;
    		break;
    	case Left :
    		level[0] += 4;	level[1] += 4;
    		level[2] += 4;	level[3] += 4; 
    		break;
    	case Right :
    		level[0] += 6;	level[1] += 6;
    		level[2] += 6;	level[3] += 6;
    		break;
    	default:
    		break;
    }

   	std::string pathCharacter = "images/Personnage/" + _character + ".png";
	if(!perso.load(pathCharacter, level, 2, 2)){
		std::cout << "Erreur du chargement du personnage" << std::endl;
	}


	return perso;
}


void TileCharacter::init_coord(sf::View &view){
	_feet_bottomleft 	= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +64));	//
    _feet_bottomright	= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +64));	// Save the coord of each
    _feet_topleft		= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +32));	// coord of character's feet
	_feet_topright		= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +32));	//
}

void TileCharacter::checkKey(sf::Event &event){
        
    // Si on appuit sur une touche
    if (event.type == sf::Event::KeyPressed){
        switch (event.key.code){
            case sf::Keyboard::Up :     _upFlag=true; break;
            case sf::Keyboard::Down:    _downFlag=true; break;
            case sf::Keyboard::Left:    _leftFlag=true; break;
            case sf::Keyboard::Right:   _rightFlag=true; break;
            default : break;
        }
    }

    // Si on relache la touche
    if (event.type == sf::Event::KeyReleased){
        switch (event.key.code){
            // Process the up, down, left and right keys
            case sf::Keyboard::Up :     _upFlag=false; break;
            case sf::Keyboard::Down:    _downFlag=false; break;
            case sf::Keyboard::Left:    _leftFlag=false; break;
            case sf::Keyboard::Right:   _rightFlag=false; break;
            default : break;
        }
    }
}
void TileCharacter::move(sf::View &view){

	sf::Vector2f next_move1;
	sf::Vector2f next_move2;

	if(_leftFlag){  // left key is pressed: move our character

		next_move1 = _feet_topleft - sf::Vector2f(-MOVESPEED, 0);
		next_move2 = _feet_bottomleft - sf::Vector2f(-MOVESPEED, 0);
		
		if( (obstacle_ville1[ abs((int) ((next_move1.y)/64)) ][ abs((int) (next_move1.x/64)) ] != -1 ) ||
			(obstacle_ville1[ abs((int) ((next_move2.y)/64)) ][ abs((int) (next_move2.x/64)) ] != -1 ) ){
			// Check if both corner touch an obstacle
			
			view.move(-MOVESPEED, 0);
		}
        
        this->load_character(Left);
    }
    else if(_rightFlag){  // right key is pressed: move our character

    	next_move1 = _feet_topright - sf::Vector2f(MOVESPEED, 0);
    	next_move2 = _feet_bottomright - sf::Vector2f(MOVESPEED, 0);
    	
    	if( (obstacle_ville1[ abs((int) ((next_move1.y)/64)) ][ abs((int) (next_move1.x/64)) ] != -1 ) ||
			(obstacle_ville1[ abs((int) ((next_move2.y)/64)) ][ abs((int) (next_move2.x/64)) ] != -1 ) ){
			// Check if both corner touch an obstacle
       		
       		view.move(MOVESPEED, 0);
       	}

        this->load_character(Right);
    }
    else if(_upFlag){     // up key is pressed: move our character

    	next_move1 = _feet_topright - sf::Vector2f(0, -MOVESPEED);
    	next_move2 = _feet_topleft - sf::Vector2f(0, -MOVESPEED);
		
		if( (obstacle_ville1[ abs((int) ((next_move1.y)/64)) ][ abs((int) (next_move1.x/64)) ] != -1 ) ||
			(obstacle_ville1[ abs((int) ((next_move2.y)/64)) ][ abs((int) (next_move2.x/64)) ] != -1 ) ){
			// Check if both corner touch an obstacle
       		
        	view.move(0, -MOVESPEED);
    	}

        this->load_character(Back);
    }
    else if(_downFlag){   // down key is pressed: move our character

    	next_move1 = _feet_bottomright - sf::Vector2f(0, MOVESPEED);
    	next_move2 = _feet_bottomleft - sf::Vector2f(0, MOVESPEED);

    	if( (obstacle_ville1[ abs((int) ((next_move1.y)/64)) ][ abs((int) (next_move1.x/64)) ] != -1 ) ||
			(obstacle_ville1[ abs((int) ((next_move2.y)/64)) ][ abs((int) (next_move2.x/64)) ] != -1 ) ){
			// Check if both corner touch an obstacle

        	view.move(0, MOVESPEED);
    	}

        this->load_character(Face);              
    }

    _feet_bottomleft 	= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +64));	//
    _feet_bottomright	= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +64));	// Save the coord of each
    _feet_topleft		= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +32));	// coord of character's feet
	_feet_topright		= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +32));	//
}

