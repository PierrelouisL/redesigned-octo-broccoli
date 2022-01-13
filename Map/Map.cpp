#include "Window.h"
#include "Map.h"

TileMap TileMap::load_map(){

	TileMap map;

	// on définit le niveau à l'aide de numéro de tuiles
	int level[ _width * _height ];

    for(unsigned int i=0; i< _width * _height; i++){
    	level[i] = i; 
    }

    if(!map.load( _path , level, _width, _height )){
    	std::cout << "Erreur lors du chargement" << std::endl;
    }

	return map;
}