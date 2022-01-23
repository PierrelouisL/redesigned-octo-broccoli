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
	static sf::Clock clk;
	static sf::Music sound_effect;

	if(get_leftflag()){  // left key is pressed: move our character
		
		set_eye(Left);
		next_case = checkFrontCase(-1, true);
		if( next_case != sf::Vector2f(-1, -1) ){
			// Check if both corner touch an obstacle	
			view.move(-MOVESPEED, 0);
		}       
    }
    else if(get_rightflag()){  // right key is pressed: move our character
    	
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

    if(clk.getElapsedTime().asSeconds() > 0.38){	// Jump time
		_gravity = false;
    }

    if(get_upflag()){
    	sound_LoadStart(sound_effect, "sound/MarioJump.wav", 10.f, false);
        set_upflag(false);
    }
    if(_gravity){ 									// Go up for the jump
    	_enable_jump = false;
		if( checkFrontCase(-1, true, sf::Vector2f(0, -100)) != sf::Vector2f(-1, -1) ){
			view.move(0, -7);
		}
		else{										// If the hit something with your head
			_gravity = false;
			view.move(0, 7);
		}
    }
    else{											// Go down
		if( checkFrontCase(-1, true, sf::Vector2f(0, 0)) != sf::Vector2f(-1, -1) ){
			view.move(0, 7);
		}
		else{										// Hit the ground
			_enable_jump = true;
		}
	}
    
    // Some event when you touch the right case in mario land
    if( checkFrontCase(10, false, sf::Vector2f(0, 0)) != sf::Vector2f(-1, -1) ){	
        view.setCenter(sf::Vector2f(22*64, 56.5*64));
    }

    this->load_character();
    init_coord(view);
}