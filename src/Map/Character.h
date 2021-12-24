#pragma once
#include "Window.h"


typedef enum orientation{ Face, Back, Left, Right } orientation;

class TileCharacter : public TileWindow{

	public:
		TileCharacter():_character("perso_Fleche"){}
		TileCharacter(const std::string &character): _character(character){}

		TileCharacter load_character(const orientation &orientation);

	private:
		std::string _character;

};