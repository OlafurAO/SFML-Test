#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"

class Level {
	public:
		Level(sf::RenderWindow* window, const char* fileName);
		~Level();
		
		void PrintXML();

	private:
		sf::RenderWindow* window;
		tinyxml2::XMLDocument doc;
};
#endif