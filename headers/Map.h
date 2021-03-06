#pragma once
#include "Window.h"

class TileMap : public TileWindow{

	public:
		TileMap():_path("images/Map/Map1.png"), _width(60), _height(61) {}
		TileMap(const std::string &path, const unsigned int &width, const unsigned int &height): _path(path), _width(width), _height(height) {}

		void load_map();
		void change_map(std::string newpath){_path = newpath;}
	private:
		std::string _path;
		unsigned int _width;
		unsigned int _height;
};


