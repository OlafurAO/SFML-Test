#pragma once

class Bullet {
	public:
		Bullet(sf::RenderWindow* window, sf::Vector2u windowSize, \
		sf::Vector2i mousePos, float weaponX, float weaponY, int playerDirection) {
			mousePos.y -= 80;
			mousePos.x += 30;

			this->window = window;
			this->windowSize = windowSize;
			this->mousePos = mousePos;
			this->weaponX = weaponX;
			this->weaponY = weaponY;
			this->playerDirection = playerDirection;

			positionX = weaponX;
			positionY = weaponY;
			bulletSpeed = 30;

			angle = atan2(weaponY - mousePos.y, weaponX - mousePos.x);

			circle = sf::CircleShape(100.f);
			circle.setFillColor(sf::Color::Yellow);
			circle.setPosition(positionX, positionY);
			circle.scale(0.1, 0.1);
		}

		~Bullet() {
			delete window;
		}

		void UpdateBullet() {
			positionX += (cos(angle) * -bulletSpeed);
			positionY += (sin(angle) * -bulletSpeed);
			circle.setPosition(positionX, positionY);

			BulletOffscreenCheck();
			DrawBullet();
		}

		void DrawBullet() {
			if (playerDirection == 1) {
				if (!(positionX - weaponX <= 20)) {
					window->draw(circle);
				}
			} else {
				if (!(weaponX - positionX < 20)) {
					window->draw(circle);
				}
			}
		}

		void BulletOffscreenCheck() {
			if (positionX > window->getSize().x || positionY > window->getSize().y \
				|| positionX < 0 || positionY < 0) {
				isBulletOffScreen = true;
			}
		}

		bool IsBulletOffScreen() {
			return isBulletOffScreen;
		}

	private:
		sf::CircleShape circle;
		sf::RenderWindow* window;
		sf::Vector2u windowSize;
		sf::Vector2i mousePos;

		bool isBulletOffScreen;

		float angle;
		float weaponX;
		float weaponY;

		float positionX;
		float positionY;
		int playerDirection;
		int bulletSpeed;

		int yDirection;
		int xDirection;
};
