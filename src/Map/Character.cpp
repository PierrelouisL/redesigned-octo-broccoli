#include "Window.h"
#include "Character.h"


TileCharacter TileCharacter::load_character(const orientation &orientation){

	TileCharacter perso;

	// on définit le niveau à l'aide de numéro de tuiles
	int level[] = { 0, 1, 8, 9 };

    switch(orientation){
    	case Face:
    		break;
    	case Back :
    		level[0] += 2;	level[1] +=	2;
    		level[2] += 2;	level[3] += 2;
    		break;
    	case Left :
    		level[0] += 4;	level[1] += 4;
    		level[2] += 4;	level[3] += 4; 
    		break;
    	case Right :
    		level[0] += 6;	level[1] += 6;
    		level[2] += 6;	level[3] += 6;
    		break;
    	default:
    		break;
    }

   	std::string pathCharacter = "images/Personnage/" + _character + ".png";
	if(!perso.load(pathCharacter, level, 2, 2)){
		std::cout << "Erreur du chargement du personnage" << std::endl;
	}

	return perso;
}

