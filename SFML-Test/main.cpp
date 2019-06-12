//SFML project setup info: https://www.sfml-dev.org/tutorials/2.5/start-vc.php
//SFML input and events: https://www.sfml-dev.org/tutorials/2.5/window-events.php
//SFML rotation and bounds: https://www.youtube.com/watch?v=wlv0lNNmpH8
//Spritesheets:
	// -- https://jfaexe.itch.io/nt-like-sprites-pack


//External tools/libraries used:	
	//tinyxml: https://github.com/leethomason/tinyxml2
		// - Using tinyxml with C++: https://www.youtube.com/watch?v=Qn2D6lq08gk 
	//STP: https://github.com/edoren/STP


//Troubleshooting:
	//Project configuration: https://www.youtube.com/watch?v=Mbk9M_R60KU&list=PLHJE4y54mpC5UT0fouyswCW9e1HStmlXL
	//Using external libraries https://youtu.be/dZr-53LAlOw?list=PLlrATfBNZ98dC-V-N3m0Go4deliWHPFwT&t=662
	//Change configuration from x86 to x64 if a linking error occurs
	//Copy these files from SFML/bin to x64/Debug:
		//- sfml-graphics-2.dll
		//- sfml-network-2.dll 
		//- sfml-system-2.dll
		//- sfml-window-2.dll


//TODO:
	//Issues/bugs:
		//- Weapon knockback doesn't work anymore
		//- Player run animation plays when shooting down?????
	//Add:
		//- Tile map integration
		//- Weapon pickup mechanic
		//- Polish weapon rotation


#include <SFML/Graphics.hpp>
#include <iostream>

#include "Player.h"
#include "Level.h"
//#include "STP/TMXLoader.hpp"

std::vector<Player> players;

void KeyboardMoveInput(sf::Vector2f& currentPosition, Player& player);
void MouseInput(Player& player, sf::RenderWindow& window);

int main(int argc, char** argv) {
	sf::RenderWindow window(sf::VideoMode(1800, 800), "Fuck This Shit"); //sf = namespace SFML
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(90);

	Player player = Player(&window, "../Resources/Art/Players/players.png", 3, 0, 0);
	sf::Event event;

	//Level level_01 = Level(&window, "../Resources/Levels/Level 1/level_01.tmx");
	//level_01.PrintXML();
	
	while (window.isOpen()) {
		sf::Vector2f currentPosition = player.GetPosition();
		KeyboardMoveInput(currentPosition, player);
		MouseInput(player, window);

		player.MovePlayer(currentPosition.x, currentPosition.y);

		while (window.pollEvent(event)) {
			//Close the application
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			
			//Window stuff
			if (event.type == sf::Event::LostFocus) {
				std::cout << "Lost Focus" << std::endl;
			} 		
			else if (event.type == sf::Event::GainedFocus) {
				std::cout << "Gained Focus" << std::endl;
			}
		}

		window.clear(sf::Color(255, 255, 255, 255));
		player.UpdatePlayer();
		window.display();
	}

	return 0;
}

void KeyboardMoveInput(sf::Vector2f& currentPosition, Player& player) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		currentPosition.y -= 5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		currentPosition.y += 5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		currentPosition.x -= 5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		currentPosition.x += 5;
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