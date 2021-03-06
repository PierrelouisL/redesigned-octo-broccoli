#include "../headers/Character.h"


#define MOVESPEED 3.5 		// Define the movespeed of the character

extern int obstacle_ville1[61][60];


void TileCharacter::load_character(){

	static sf::Clock clk;

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
    if(oneMoveFlag()){
    	if(clk.getElapsedTime().asSeconds() > 0.15f){	// Change sprite while in movement
	    	if(_n_sprite == 4){
				_n_sprite = 1;
			}
			else{
				_n_sprite += 1; 
			}
			clk.restart();
	    }
    }
    else{
    	_n_sprite = 1;
    }

   	std::string pathCharacter = "images/Personnage/" + _character + std::to_string(_n_sprite) + ".png";
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


sf::Vector2f TileCharacter::checkFrontCase(int val, bool flag){

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

	if(!flag){
		if(obstacle_ville1[ abs((int) ((next_case1.y)/64)) ][ abs((int) (next_case1.x/64)) ] == val){
			return next_case1;
		}
		else{
			return sf::Vector2f(-1, -1);	// Aucune case
		}
	}
	else{
		if(obstacle_ville1[ abs((int) ((next_case1.y)/64)) ][ abs((int) (next_case1.x/64)) ] > val){
			return next_case1;
		}
		else{
			return sf::Vector2f(-1, -1);	// Aucune case
		}
	}
}

sf::Vector2f TileCharacter::checkFrontCase(int val, bool flag, sf::Vector2f offset){
	// Default bottom of the feet
	sf::Vector2f next_case1 = _feet_bottomright + offset;
	sf::Vector2f next_case2 = _feet_bottomleft  + offset;

	next_case1 = next_case1 + next_case2;
	next_case1 = next_case1/2.f;

	if(!flag){
		if(obstacle_ville1[ abs((int) ((next_case1.y)/64)) ][ abs((int) (next_case1.x/64)) ] == val){
			return next_case1;
		}
		else{
			return sf::Vector2f(-1, -1);	// Aucune case
		}
	}
	else{
		if(obstacle_ville1[ abs((int) ((next_case1.y)/64)) ][ abs((int) (next_case1.x/64)) ] > val){
			return next_case1;
		}
		else{
			return sf::Vector2f(-1, -1);	// Aucune case
		}
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
		next_case = checkFrontCase(-1, true);
		if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle	
			view.move(-MOVESPEED, 0);
		}       
    }
    else if(_rightFlag){  // right key is pressed: move our character
    	
    	_eye = Right;
    	next_case = checkFrontCase(-1, true);
    	if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle
       		view.move(MOVESPEED, 0);
       	}
    }
    else if(_upFlag){     // up key is pressed: move our character
		
		_eye = Back;
		next_case = checkFrontCase(-1, true);
		if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle
        	view.move(0, -MOVESPEED);
    	}
    }
    else if(_downFlag){   // down key is pressed: move our character
		_eye = Face; 
		next_case = checkFrontCase(-1, true);
    	if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle
        	view.move(0, MOVESPEED);
    	}           
    }

    this->load_character();
    init_coord(view);
}


