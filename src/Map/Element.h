#pragma once
#include "Map.h"
#include <vector>

class TileElement : public TileMap{
	public:
		void load_allElement(sf::RenderWindow &window);

		void put_VectorType(int val);
		void put_VectorElement(TileMap element);
		void put_VectorCoord(sf::Vector2f coord);

		void addTree(){_nb_tree++;}

		int getNbTree(){return _nb_tree;}
	private:

		std::vector<int> _vector_type;
		std::vector<TileMap> _vector_element;
		std::vector<sf::Vector2f> _vector_coord;

		int _nb_tree;
};