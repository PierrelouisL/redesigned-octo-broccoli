#include "Element.h"

void TileElement::load_allElement(sf::RenderWindow &window){


	for(unsigned int i = 0; i < _vector_element.size(); i++){
		window.draw(_vector_element[i]);
		
		if(_vector_type[i] == 5){									// If  vector_element[i] is a car
			_vector_element[i].move(-5, 0);
			if(_vector_element[i].getPosition().x < 0){
				_vector_element.erase(_vector_element.begin() + i);
				_vector_type.erase(_vector_type.begin() + i);
			}
		}
	}

}

bool TileElement::check_collision(sf::Vector2f coords){
	for(unsigned int i = 0; i < _vector_element.size(); i++){
		if(_vector_type[i] == 3){
			if(coords.x/64 + 1 > _vector_element[i].getPosition().x/64 && coords.x/64 - 1 < _vector_element[i].getPosition().x/64){
				if((coords.y/64 +0.5) > _vector_element[i].getPosition().y/64 && (coords.y/64-0.5) < _vector_element[i].getPosition().y/64){
					return true;
				}	
			}
		}
	}
	return false;
}

void TileElement::put_VectorType(int val){
	_vector_type.push_back(val);
}

void TileElement::put_VectorElement(TileMap element){
	_vector_element.push_back(element);
}

void TileElement::put_VectorCoord(sf::Vector2f coord){
	_vector_coord.push_back(coord);
}