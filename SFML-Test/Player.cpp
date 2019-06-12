#include "Player.h"

enum PlayerDirection {
	LEFT = -1,
	RIGHT = 1
};

Player::Player(sf::RenderWindow* window, std::string playerImage, int startingCellIndex,\
int positionX, int positionY) : spritesheet(window, playerImage, 16, 17) {
	this->startingCellIndex = startingCellIndex;
	this->positionX = positionX;
	this->positionY = positionY;
	this->window = window;

	cellX = startingCellIndex;
	cellY = 0;

	playerDirection = RIGHT;

	playerJumping = false;
	playerMoving = false;
	playerArmed = false;

	PlayerWeaponPickup();
}

Player::~Player() {
	//delete window;
	delete weapon;
}

void Player::UpdatePlayer() {
	if (playerJumping) {
		JumpHandler();
	}

	if (playerMoving) {
		MoveAnimationController();
	} else {
		IdleAnimationController();
	}
	
	CheckTurnAround();
	DrawPlayer();

	if (playerArmed) {
		weapon->UpdateWeapon(sf::Mouse::getPosition(), positionX, positionY, playerDirection);
	}
}

void Player::DrawPlayer() {
	spritesheet.DrawSprite(cellX, cellY, playerDirection);
}

void Player::CheckTurnAround() {
	if (sf::Mouse::getPosition().x > positionX) {
		if (playerDirection == LEFT) {
			playerDirection = RIGHT;
			cellX = 3;
		}
	}

	else if (sf::Mouse::getPosition().x < positionX) {
		if (playerDirection == RIGHT) {
			playerDirection = LEFT;
			cellX = 4;
		}
	}
}

/////////////////////////////////Movement methods
void Player::MovePlayer(float positionX, float positionY) {
	if (this->positionX == positionX && this->positionY == positionY) {
		playerMoving = false;
		return;
	} 

	spritesheet.MoveSprite(positionX, positionY);
	this->positionX = positionX;
	this->positionY = positionY;

	playerMoving = true;
}

void Player::JumpHandler() {
	if (jumpTimer.getElapsedTime().asSeconds() < 0.3) {	
		MovePlayer(positionX, positionY - 10);
	} 
	
	//TODO: replace this block with gravity
	else if (jumpTimer.getElapsedTime().asSeconds() > 0.3 && \
	!(jumpTimer.getElapsedTime().asSeconds() > 0.6)) {
		MovePlayer(positionX, positionY + 10);
	} 
	
	else {
		playerJumping = false;
	}
}

void Player::PlayerJump() {
	//Only allow player to jump once
	if (!playerJumping) {
		playerJumping = true;
		jumpTimer.restart();
	}
}

void Player::WeaponKickback() {
	int kickback = weapon->GetWeaponKickback();

	if (sf::Mouse::getPosition().y - 200 > positionY) {
		positionY -= kickback;
	}

	//positionX += kickback * (playerDirection * -1);
	//spritesheet.MoveSprite(positionX, positionY);
}

////////////////////////////////////Weapon methods
void Player::PlayerWeaponPickup() {
	weapon = new Weapon(window);
	playerArmed = true;
}

void Player::PlayerAttack(sf::Vector2i mousePos) {
	if (playerArmed) {
		if (weapon->IsWeaponReady()) {
			weapon->AttackWeapon(mousePos, positionX, positionY, playerDirection);
			WeaponKickback();
		}
	}
}

/////////////////////////////////Animation methods
void Player::IdleAnimationController() {
	if (playerDirection == RIGHT) {
		if (cellX < 3 || cellX > 6) {
			cellX = 3;
		} else {
			if (animationTimer.getElapsedTime().asSeconds() > 0.1f) {
				animationTimer.restart();
				cellX++;

				if (cellX == 7) {
					cellX = 3;
				}
			}
		}
	} else {
		if (cellX < 4 || cellX > 7) {
			cellX = 4;
		} else {
			if (animationTimer.getElapsedTime().asSeconds() > 0.1f) {
				animationTimer.restart();
				cellX++;

				if (cellX == 8) {
					cellX = 4;
				}
			}
		}
	}

	cellY = 0;
}

void Player::MoveAnimationController() {
	if (playerDirection == RIGHT) {
		if (cellX < 3 || cellX > 7) {
			cellX = 3;
		}
		else {
			if (animationTimer.getElapsedTime().asSeconds() > 0.1f) {
				animationTimer.restart();
				cellX++;

				if (cellX == 8) {
					cellX = 3;
				}
			}
		}
	} else {
		if (cellX < 4 || cellX > 8) {
			cellX = 4;
		}
		else {
			if (animationTimer.getElapsedTime().asSeconds() > 0.1f) {
				animationTimer.restart();
				cellX++;

				if (cellX == 9) {
					cellX = 4;
				}
			}
		}
	}
	
	cellY = 1;
}

///////////////////////////////////////Get Methods
sf::Vector2f Player::GetPosition() {
	return sf::Vector2f(positionX, positionY);
}