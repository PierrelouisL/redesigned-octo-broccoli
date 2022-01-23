#pragma once
#include "Window.h"
#include "Element.h"


class TileCharacter : public TileWindow{

	public:
		TileCharacter():_character("perso_Fleche"), _eye(Face), _upFlag(false), _downFlag(false), _leftFlag(false), _rightFlag(false), _is_main_character(true){}
		TileCharacter(const std::string &character): _character(character), _eye(Face), _upFlag(false), _downFlag(false), _leftFlag(false), _rightFlag(false), _is_main_character(true){}
		TileCharacter(const TileCharacter& T);
		void load_character();

		void init_coord(sf::View &view); // If main character
		void init_coord(sf::Vector2f coords); // If bot
		sf::Vector2f checkFrontCase(int val);
		void checkKeyMove(sf::Event &event);
		void move(sf::View &view);
		void actionKey(sf::Event &event, TileElement &element, bool* heal);
		void resetkey(){_upFlag = false; _downFlag = false; _leftFlag = false; _rightFlag = false;}
		void change_char(std::string character){_character = character;};
		bool oneMoveFlag(){return _upFlag || _downFlag || _leftFlag || _rightFlag;}

		void set_char(std::string character){_character = character;}
		void set_eye(orientation val){_eye = val;}
		void set_upflag	(bool val)	{_upFlag 	= val;}
		void set_downflag(bool val)	{_downFlag 	= val;}
		void set_leftflag(bool val)	{_leftFlag 	= val;}
		void set_rightflag(bool val){_rightFlag = val;}
		void set_feet_topleft(sf::Vector2f val)		{_feet_topleft 		= val;}
		void set_feet_topright(sf::Vector2f val)	{_feet_topright 	= val;}
		void set_feet_bottomleft(sf::Vector2f val)	{_feet_bottomleft	= val;}
		void set_feet_bottomright(sf::Vector2f val)	{_feet_bottomright 	= val;}


		orientation get_eye(){return _eye;}
		bool get_upflag()	{return _upFlag 	;}
		bool get_downflag()	{return _downFlag 	;}
		bool get_leftflag()	{return _leftFlag 	;}
		bool get_rightflag(){return _rightFlag 	;}
		
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