#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>

class TileWindow : public sf::Drawable, public sf::Transformable{

	public:

		TileWindow(){};
		
		bool load(const std::string& tileset, const int* tiles, unsigned int width, unsigned int height);
		void sound_LoadStart(sf::Music &music, std::string name, float volume, bool loop);

	private:

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const{
	        // on applique la transformation
	        states.transform *= getTransform();

	        // on applique la texture du tileset
	        states.texture = &m_tileset;

	        // et on dessine enfin le tableau de vertex
	        target.draw(m_vertices, states);
	    }

	    sf::VertexArray m_vertices;
	    sf::Texture m_tileset;

};