#pragma once
#include "Window.h"
#include "Element.h"
#include "Character.h"
#include <SFML/Audio.hpp>

class TileCharacterMario : public TileCharacter{

	public:

		TileCharacterMario(): TileCharacter(), _gravity(false), _enable_jump(false){}
		TileCharacterMario(TileCharacter &character): TileCharacter(character), _gravity(true), _enable_jump(false){}

		void checkKeyMove(sf::Event &event);
		void move(sf::View &view);
		
	private:
		
		bool _gravity;
		bool _enable_jump;
};