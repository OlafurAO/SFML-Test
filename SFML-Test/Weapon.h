#pragma once

#ifndef WEAPON_H
#define WEAPON_H

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Bullet.h"

enum WeaponTypes {
	BATON = 0,
	PISTOL = 1, 
	SMG = 2, 
	SHOTGUN_ONE = 3,
	GRENADELAUNCHER_ONE = 4
};

const double rateOfFireList[] = {
	0.2, //BATON
	0.2, //PISTOl
	0, //SMG
	0.5, //SHOTGUN_ONE
	2 //GRENADELAUNCHER_ONE
};

const int kickbackList[] = {
	0, //BATON
	20, //PISTOl
	5, //SMG
	50, //SHOTGUN_ONE
	20 //GRENADELAUNCHER_ONE
};

const float PI = 3.14159265;

class Weapon {
	public:
		Weapon(sf::RenderWindow* window) {
			this->window = window;

			spritesheet = "../Resources/Art/Weapons/Weapons.png";
			texture.loadFromFile(spritesheet);

			weaponType = SMG;

			spriteRightRect = sf::IntRect(21 * weaponType, 0, 21, 6.833333333333333);
			spriteLeftRect = sf::IntRect(21 * (weaponType + 1), 0, -21, 6.833333333333333);

			sprite = sf::Sprite(texture, spriteRightRect);
			sprite.scale(5, 5);

			fireCounter.restart();

			fireRate = 0;
		}

		Weapon() {
			std::cout << "Piss";
		}

		~Weapon() {
			for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++) {
				delete (*it);
			}

			bullets.clear();
			delete window;
		}

		void UpdateWeapon(sf::Vector2i mousePos, int x, int y, int playerDirection) {
			RotateWeapon(mousePos, x, y, playerDirection);
			DrawWeapon(x, y, playerDirection);
			//DrawLaserSight(mousePos, x, y, playerDirection);
			UpdateBullets();
		}

		void UpdateBullets() {
			if (bullets.size() > 0) {
				for (std::vector<Bullet*>::iterator it = bullets.begin(); it != bullets.end(); it++) {
					(*it)->UpdateBullet();

					if ((*it)->IsBulletOffScreen()) {
						bullets.erase(it--);
					}
				}
			}
		}

		void AttackWeapon(sf::Vector2i mousePos, int playerX, int playerY, int playerDirection) {
			if (fireCounter.getElapsedTime().asSeconds() >= fireRate) {
				bullets.push_back(new Bullet(window, window->getSize(), \
					mousePos, sprite.getPosition().x, sprite.getPosition().y, playerDirection));

				fireCounter.restart();

				if (fireRate == 0) {
					fireRate = rateOfFireList[weaponType];
				}
			}
		}

		void RotateWeapon(sf::Vector2i mousePos, int x, int y, int playerDirection) {
			float dX = mousePos.x - x;
			float dY = mousePos.y - y;
			int multiplier;

			if (playerDirection == 1) {
				sprite.setOrigin(5.f, 1.f);
				dY -= 180;
			} 
			else if (playerDirection == -1) {
				sprite.setOrigin(15.f, 1.f);
				dY -= 180;
			}

			float rotation = atan2(playerDirection * dY, playerDirection * dX);
			rotation *= 180 / PI;
			
			sprite.setRotation(rotation);
		}

		void DrawWeapon(int x, int y, int playerDirection) {
			if (playerDirection == 1) {
				sprite.setTextureRect(spriteRightRect);
				sprite.setPosition(x + 45, y + 50);
			}
			else if (playerDirection == -1) {
				sprite.setTextureRect(spriteLeftRect);
				sprite.setPosition(x + 30, y + 50);
			}

			window->draw(sprite);
		}

		void DrawLaserSight(sf::Vector2i mousePos, int x, int y, int playerDirection) {
			sf::Vector2f playerFix;
			sf::Vector2f mouseFix;

			if (playerDirection == 1) {
				playerFix = sf::Vector2f(100, 40);
				mouseFix = sf::Vector2f(-40, -170);
			}
			else if (playerDirection == -1) {
				playerFix = sf::Vector2f(-20, 41);
				mouseFix = sf::Vector2f(40, -170);
			}

			sf::Vertex line[2] = {
				sf::Vector2f(x + playerFix.x, y + playerFix.y),
				sf::Vector2f(mousePos.x + mouseFix.x, mousePos.y + mouseFix.y)
			};

			line[0].color = sf::Color::Red;

			window->draw(line, 2, sf::Lines);
		}

		int GetWeaponKickback() {
			return kickbackList[weaponType];
		}

		bool IsWeaponReady() {
			return fireCounter.getElapsedTime().asSeconds() >= fireRate;
		}

	private:
		sf::RenderWindow* window;
		sf::Texture texture;
		sf::IntRect spriteRightRect;
		sf::IntRect spriteLeftRect;
		sf::Sprite sprite;
		sf::Clock fireCounter;

		std::vector<Bullet*> bullets;
		std::string spritesheet;

		WeaponTypes weaponType;

		double fireRate;
};

#endif