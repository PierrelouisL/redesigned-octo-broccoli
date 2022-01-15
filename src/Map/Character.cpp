#include "Character.h"
#include "Obstacle.h"
#include <wait.h>

#define MOVESPEED 10

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


void TileCharacter::init_coord(sf::View &view){
	_feet_bottomleft 	= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +64));	//
    _feet_bottomright	= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +64));	// Save the coord of each
    _feet_topleft		= sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +32));	// coord of character's feet
	_feet_topright		= sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +32));	//
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
			next_case1 = _feet_topright + sf::Vector2f(0, -25);
			next_case2 = _feet_topleft + sf::Vector2f(0, -25);
			break;
		case Face:
			next_case1 = _feet_bottomright + sf::Vector2f(0, 25);
			next_case2 = _feet_bottomleft + sf::Vector2f(0, 25);   		
			break;
		default:
			break;
	}

	if(obstacle_ville1[ abs((int) ((next_case1.y)/64)) ][ abs((int) (next_case1.x/64)) ] == val){
		return next_case1;
	}
	else if(obstacle_ville1[ abs((int) ((next_case2.y)/64)) ][ abs((int) (next_case2.x/64)) ] == val ){
		return next_case2;
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

void TileCharacter::actionKey(sf::Event &event, TileElement &element){
	
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

				temp_element.setPosition(sf::Vector2f((int) (next_case.x/64)*64, (int) ((next_case.y)/64)*64) + sf::Vector2f(-2, -80)); 		
				element.put_VectorElement(temp_element);
				element.put_VectorType(2);
	    	}
	    }

	    if(oneMoveFlag()){
	    	sf::Vector2f next_case = checkFrontCase(5);
	    	
	    	if( next_case != sf::Vector2f(-1, -1) ){

	    		obstacle_ville1[ abs((int) ((next_case.y)/64)) ][ abs((int) (next_case.x/64)) ] = 0;

				TileMap temp_element;
	    		int level[] = { 0, 1, 2, 3};
	    		
				if(!temp_element.load("images/voiture.png", level, 2, 2)){
					std::cout << "Erreur du chargement de l'élément" << std::endl;
				}

				temp_element.setPosition(sf::Vector2f((int) (next_case.x/64)*64, (int) ((next_case.y)/64)*64) + sf::Vector2f(640, -64)); 		
				element.put_VectorElement(temp_element);
				element.put_VectorType(3);
	    	}
	    }
    } 
}



