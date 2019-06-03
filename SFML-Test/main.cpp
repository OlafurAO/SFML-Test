#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
//#include "tmxlite/Map.hpp"


//SFML project setup info: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
//SFML input and events: https://www.sfml-dev.org/tutorials/2.5/window-events.php
//SFML rotation and bounds: https://www.youtube.com/watch?v=wlv0lNNmpH8
//Spritesheets:
	//-- https://jfaexe.itch.io/nt-like-sprites-pack


//External tools/libraries used:
	//-- Cmake: https://cmake.org/download/
	//-- tmxlite: https://github.com/fallahn/tmxlite
		//-- tmxlite wiki: https://github.com/fallahn/tmxlite/wiki


//Troubleshooting:
	//--Project configuration: https://www.youtube.com/watch?v=Mbk9M_R60KU&list=PLHJE4y54mpC5UT0fouyswCW9e1HStmlXL
	//--Change configuration from x86 to x64 if a linking error occurs
	//--Copy these files from SFML/bin to x64/Debug:
		//sfml-graphics-2.dll, sfml-network-2.dll, 
		//sfml-system-2.dll, sfml-window-2.dll

std::vector<Player> players;

void KeyboardMoveInput(sf::Vector2f& currentPosition, Player& player);
void KeyboardEventInput(sf::Vector2f& currentPosition, Player& player);
void MouseInput(Player& player, sf::RenderWindow& window);

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(1800, 800), "SFML works!"); //sf = namespace SFML
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(90);

	Player player = Player(&window, "../Resources/Art/Players/players.png", 3, 0, 0);
	sf::Event event;

	while (window.isOpen()) {
		sf::Vector2f currentPosition = player.GetPosition();
		KeyboardMoveInput(currentPosition, player);
		player.MovePlayer(currentPosition.x, currentPosition.y);

		MouseInput(player, window);

		while (window.pollEvent(event)) {
			//Close the application
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			///////////////////////////////////////////////////
			/////////////////////////////Keyboard input
			if (event.type == sf::Event::KeyPressed) {
				KeyboardEventInput(currentPosition, player);
			}
			///////////////////////////////////////////////////
			///////////////////////////////Window stuff
			if (event.type == sf::Event::LostFocus) {
				std::cout << "Lost Focus" << std::endl;
			} 		
			
			else if (event.type == sf::Event::GainedFocus) {
				std::cout << "Gained Focus" << std::endl;
			}
			///////////////////////////////////////////////////
		}

		window.clear(sf::Color(255, 255, 255, 255));

		player.UpdatePlayer();

		window.display();
	}

	return 0;
}

void KeyboardMoveInput(sf::Vector2f& currentPosition, Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		//std::cout << "W button pressed" << std::endl;
		currentPosition.y -= 5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		//std::cout << "S button pressed" << std::endl;
		currentPosition.y += 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		//std::cout << "A button pressed" << std::endl;
		currentPosition.x -= 5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		//std::cout << "D button pressed" << std::endl;
		currentPosition.x += 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		//std::cout << "Up arrow pressed" << std::endl;
	}
}

void KeyboardEventInput(sf::Vector2f& currentPosition, Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		std::cout << "Escape button pressed" << std::endl;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		player.PlayerJump();
	}
}

void MouseInput(Player& player, sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		player.PlayerAttack(sf::Mouse::getPosition(window)); 		
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

	}
}