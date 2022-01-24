#pragma once
#include "Map.h"
#include <vector>

class TileElement : public TileMap{
	public:
		void load_allElement(sf::RenderWindow &window);
		bool check_collision(sf::Vector2f coord_player);
		void addTree(){_nb_tree++;}

		// Setter
		void put_VectorType(int val);
		void put_VectorElement(TileMap element);
		void put_VectorCoord(sf::Vector2f coord);

		// Getter
		int getNbTree(){return _nb_tree;}

		private:

		std::vector<int> _vector_type;				// Type of the element
		std::vector<TileMap> _vector_element;		// Element we will add to the map
		std::vector<sf::Vector2f> _vector_coord;	// Coord of the element

		int _nb_tree;
};