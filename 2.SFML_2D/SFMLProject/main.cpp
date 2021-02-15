#include <SFML\Graphics.hpp>
//#include "SFML-2.5.1/include/SFML/Graphics.hpp"

// Window Parameters
const int S_WIDTH = 1024;
const int S_HEIGHT = 768;

sf::Vector2f viewSize(S_WIDTH, S_HEIGHT);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "SFLM Project!", sf::Style::Default);

int main(void) {
	
	// Initialize Game Object
	while (window.isOpen()) {
		
		// Handle Keyboard Events
		// Update Game Objects in the scene
		// Render Game Objects
	}
}