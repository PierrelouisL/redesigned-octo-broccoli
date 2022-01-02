#pragma once
#include "Window.h"

class TileMap : public TileWindow{

	public:
		TileMap():_path("images/Ville_proto1.png"), _width(59), _height(39) {}
		TileMap(const std::string &path, const unsigned int &width, const unsigned int &height): _path(path), _width(width), _height(height) {}

		TileMap load_map();

	private:
		std::string _path;
		unsigned int _width;
		unsigned int _height;
};


