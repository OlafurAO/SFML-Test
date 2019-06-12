#pragma once

#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include "SFML/Graphics.hpp"

#include <fstream>
#include <string>

class Spritesheet {
	public:
		Spritesheet() {}
		Spritesheet(sf::RenderWindow* window, std::string spritesheet, int col, int rows) {			
			this->window = window;
			this->texture.loadFromFile(spritesheet);

			spriteRightRect = sf::IntRect(3 * 16, 0, col, rows);
			spriteLeftRect = sf::IntRect(3 * 16, 0, -col, rows);

			sprite = sf::Sprite(texture, spriteRightRect);
			sprite.scale(5, 5);

			this->col = col;
			this->rows = rows;
		}

		~Spritesheet() {
		}

		//If this doesn't work, change from "Debug" to "Release"
		void DrawSprite(int cellX, int cellY, int playerDirection) {
			if (playerDirection == 1) {
				sprite.setTextureRect(spriteRightRect);
				spriteRightRect.top = cellY * rows;
				spriteRightRect.left = cellX * col;
			}
			else if (playerDirection == -1) {
				sprite.setTextureRect(spriteLeftRect);
				spriteLeftRect.top = cellY * rows;
				spriteLeftRect.left = cellX * col;
			}

			window->draw(sprite);
		}

		void MoveSprite(float x, float y) {
			sprite.setPosition(x, y);
		}

	private:
		sf::RenderWindow* window;
		sf::Texture texture;
		sf::Sprite sprite;

		sf::RectangleShape shape;
		sf::IntRect spriteRightRect;
		sf::IntRect spriteLeftRect;

		int col;
		int rows;
};

#endif
