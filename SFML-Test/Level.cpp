#include "Level.h"

Level::Level(sf::RenderWindow* window, const char* fileName) {
	this->window = window;
	//doc.LoadFile(fileName);
	//const tinyxml2::XMLNode* node = doc.FirstChild();
}

Level::~Level() {
	//delete window;
}

void Level::PrintXML() {
	doc.Print();
}
