#pragma once

#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>

class Tile {
	public:
		Tile(sf::RenderWindow* window, sf::Texture tileset, sf::Vector2i tilesetPos, \
		sf::Vector2i position, sf::Vector2i size) {
			this->window = window;
			this->tileset = tileset;
			this->tilesetPos = tilesetPos;
			this->position = position;
			this->size = size;

			spriteRect = sf::IntRect(tilesetPos.x, tilesetPos.y, size.x, size.y);
		}

		~Tile() {
		}

		void UpdateTile() {

		}

		void DrawTile() {
			window->draw(sprite);
		}

	private:
		sf::RenderWindow* window;
		sf::Texture tileset;
		sf::Sprite sprite;
		sf::IntRect spriteRect;
		sf::Vector2i tilesetPos;
		sf::Vector2i position;
		sf::Vector2i size;
};

#endif