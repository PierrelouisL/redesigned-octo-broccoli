#include "CharacterMario.h"

#define MOVESPEED 3.5


void TileCharacterMario::checkKeyMove(sf::Event &event){
        
    // Si on appuit sur une touche
    if (event.type == sf::Event::KeyPressed){
        switch (event.key.code){
            case sf::Keyboard::Up :     set_upflag(true); if(_enable_jump){_gravity = true;}		break;
            case sf::Keyboard::Left:    set_leftflag(true); 	break;
            case sf::Keyboard::Right:   set_rightflag(true); 	break;
            default : break;
        }
    }

    // Si on relache la touche
    if (event.type == sf::Event::KeyReleased){
        switch (event.key.code){
            // Process the up, down, left and right keys
            case sf::Keyboard::Up :     set_upflag(false); 		break;
            case sf::Keyboard::Left:    set_leftflag(false); 	break;
            case sf::Keyboard::Right:   set_rightflag(false); 	break;
            default : break;
        }
    }
}

void TileCharacterMario::move(sf::View &view){	// Allow player to move in different direction at the same time ( for gravity )
	  
	sf::Vector2f next_case;
	orientation temp_eye = get_eye();
	static sf::Clock clk;
	static sf::Music music;

	if(get_leftflag()){  // left key is pressed: move our character
		
		temp_eye = Left;
		set_eye(Left);
		next_case = checkFrontCase(-1, true);
		if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle	
			view.move(-MOVESPEED, 0);
		}       
    }
    else if(get_rightflag()){  // right key is pressed: move our character
    	
    	temp_eye = Right;
    	set_eye(Right);
    	next_case = checkFrontCase(-1, true);
    	if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle
       		view.move(MOVESPEED, 0);
       	}
    }

    if(_enable_jump){
    	clk.restart();
    }

    if(clk.getElapsedTime().asSeconds() > 0.37){	// Jump time
		_gravity = false;
    }

    if(get_upflag()){
    	music.openFromFile("sound/MarioJump.wav");
        music.setVolume(10.f);
        music.play();
        set_upflag(false);
    }
    if(_gravity){ 									// Go up for the jump
    	_enable_jump = false;
    	set_eye(Back); 
		next_case = checkFrontCase(-1, true);
		if( next_case != sf::Vector2f(-1, -1) ){
			view.move(0, -6);
		}
		else{										// If the hit something with your head
			_gravity = false;
			view.move(0, 6);
		}
		
    }
    else{											// Go down
    	set_eye(Face); 
		next_case = checkFrontCase(-1, true);
		if( next_case != sf::Vector2f(-1, -1) ){
			view.move(0, 7);
		}
		else{										// Hit the ground
			_enable_jump = true;
		}
	}
    
    // Some event when you touch the right case in mario land
    set_eye(Face);
    if( checkFrontCase(10, false) != sf::Vector2f(-1, -1) ){	
        view.setCenter(sf::Vector2f(22*64, 56.5*64));
    }

	set_eye(temp_eye);
    this->load_character();

    set_feet_bottomleft	(sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +64)));	//
    set_feet_bottomright(sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +64)));	// Save the coord of each
    set_feet_topleft	(sf::Vector2f(view.getCenter() + sf::Vector2f(-32, +32)));	// corner of character's feet
	set_feet_topright	(sf::Vector2f(view.getCenter() + sf::Vector2f(+32, +32)));	//
}