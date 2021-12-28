#pragma once
#include "Window.h"


typedef enum orientation{ Face, Back, Left, Right } orientation;

class TileCharacter : public TileWindow{

	public:
		TileCharacter():_character("perso_Fleche"), _upFlag(false), _downFlag(false), _leftFlag(false), _rightFlag(false){}
		TileCharacter(const std::string &character): _character(character), _upFlag(false), _downFlag(false), _leftFlag(false), _rightFlag(false){}

		TileCharacter load_character(const orientation &orientation);
		
		void init_coord(sf::View &view);
		void checkKey(sf::Event &event);
		void move(sf::View &view);

	private:
		std::string _character;

		sf::Vector2f _feet_topleft;
		sf::Vector2f _feet_topright;
		sf::Vector2f _feet_bottomleft;
		sf::Vector2f _feet_bottomright;

		// Flags for key pressed
	    bool _upFlag;
	    bool _downFlag;
	    bool _leftFlag;
	    bool _rightFlag;

};