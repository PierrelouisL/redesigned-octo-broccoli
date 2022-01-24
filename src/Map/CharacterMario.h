#pragma once
#include "Window.h"
#include "Element.h"
#include "Character.h"

class TileCharacterMario : public TileCharacter{

	public:

		TileCharacterMario(): TileCharacter(), _gravity(true), _enable_jump(false){}
		TileCharacterMario(TileCharacter &character): TileCharacter(character), _gravity(true), _enable_jump(false){}

		void checkKeyMove(sf::Event &event);	// Change how we check pressed key
		void move(sf::View &view);				// Change how character move to mario like move
		
	private:
		
		bool _gravity;		// True : gravity on, False gravity off
		bool _enable_jump;	// Allow character to jump
};