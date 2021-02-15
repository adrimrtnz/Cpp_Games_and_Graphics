#include <SFML/Graphics.hpp>
//#include "SFML-2.5.1/include/SFML/Graphics.hpp"

// Window Parameters
const int S_WIDTH = 1024;
const int S_HEIGHT = 768;

sf::Vector2f viewSize(S_WIDTH, S_HEIGHT);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "SFLM Project", sf::Style::Default);

int main(void) {
	
	// Draw a rectangle
	sf::RectangleShape rect(sf::Vector2f(500.f, 300.f));
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(viewSize.x / 2, viewSize.y / 2);
	rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));

	// Initialize Game Object
	while (window.isOpen()) {
		
		// Handle Keyboard Events
		// Update Game Objects in the scene

		window.clear(sf::Color::Red);
		// Render Game Objects
		window.draw(rect);

		window.display();
	}
}