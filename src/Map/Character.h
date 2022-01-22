#pragma once
#include "Window.h"
#include "Element.h"

typedef enum orientation{ Face, Back, Left, Right } orientation;

class TileCharacter : public TileWindow{

	public:
		TileCharacter():_character("Greta"), _eye(Face), _n_sprite(1), _upFlag(false), _downFlag(false), _leftFlag(false), _rightFlag(false), _is_main_character(true){}
		TileCharacter(const std::string &character): _character(character), _eye(Face), _n_sprite(1), _upFlag(false), _downFlag(false), _leftFlag(false), _rightFlag(false), _is_main_character(true){}

		void load_character();

		void init_coord(sf::View &view); 					// If main character
		void init_coord(sf::Vector2f coords); 				// If bot
		sf::Vector2f checkFrontCase(int val, bool flag);	// flag : false to compare val and the case, true to compare if val is > 
		void checkKeyMove(sf::Event &event);
		void move(sf::View &view);
		void actionKey(sf::Event &event, TileElement &element, sf::View &view);
		bool oneMoveFlag(){return _upFlag || _downFlag || _leftFlag || _rightFlag;}

		void change_char(std::string character){_character = character;};

		orientation get_eye(){return _eye;}
		
	private:
		std::string _character;				// character's name
		orientation _eye;					// character's view
		int _n_sprite;				// number of the sprite to load 

		sf::Vector2f _feet_topleft;			// Top left corner of character's feet
		sf::Vector2f _feet_topright;		// Top right corner of character's feet 
		sf::Vector2f _feet_bottomleft;		// Bottom left corner of character's feet
		sf::Vector2f _feet_bottomright;		// Bottom right corner of charracter's feet

	    bool _upFlag;						// 
	    bool _downFlag;						//	Mouvement key flag
	    bool _leftFlag;						//
	    bool _rightFlag;					//

		bool _is_main_character; 		// Is the character the playable character

};