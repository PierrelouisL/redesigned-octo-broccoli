#include "Window.h"
#include "Map.h"

void TileMap::load_map(){

	// on définit le niveau à l'aide de numéro de tuiles
	int level[ _width * _height ];

    for(unsigned int i=0; i< _width * _height; i++){
    	level[i] = i; 
    }

    if(!this->load( _path , level, _width, _height )){
    	std::cout << "Erreur lors du chargement" << std::endl;
    }
}