#pragma once
#include "Window.h"
#include "Character.h"

class TileGoal : public TileCharacter{

	public:

		TileGoal(): _nTree(0), _goalTree(false), _goalCamera(false), _goalTrump(false){_NiceFont.loadFromFile("images/webpixel bitmap_medium.otf");}
	
		void display_goal(sf::RenderWindow &window, sf::Vector2f center);	// Display HUD

		void add_tree(){_nTree++; if(_nTree == 31){_goalTree = true;}}
		void done_goalCamera(){_goalCamera = true;}

		// Getter
		bool get_goalTree(){return _goalTree;}
		
	private:
		
		sf::Font _NiceFont;

		int _nTree;

		bool _goalTree;
		bool _goalCamera;
		bool _goalTrump;
};