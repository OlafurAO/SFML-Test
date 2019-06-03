#pragma once

#include <iostream>

#include "SFML/Graphics.hpp"
#include "Spritesheet.h"
#include "Weapon.h"

class Player {
	public:
		Player(sf::RenderWindow* window, std::string playerImage, \
			   int startingCellIndex, int positionX, int positionY);

		~Player();

		void UpdatePlayer();
		void DrawPlayer();
		void CheckTurnAround();

		//Movement
		void MovePlayer(float positionX, float positionY);
		void PlayerJump();
		void JumpHandler();
		void WeaponKickback();

		//Weapons
		void PlayerWeaponPickup();
		void PlayerAttack(sf::Vector2i mousePos);

		//Animation methods
		void IdleAnimationController();
		void MoveAnimationController();

		//Get methods
		sf::Vector2f GetPosition();
	
	private:
		sf::RectangleShape shape;
		sf::RenderWindow* window;
		sf::Clock animationTimer;
		sf::Clock jumpTimer;

		Spritesheet spritesheet;
		Weapon* weapon;

		float positionX;
		float positionY;
		int startingCellIndex;
		int playerDirection;
		int cellX;
		int cellY;

		bool playerJumping;
		bool playerMoving;
		bool playerArmed;
};