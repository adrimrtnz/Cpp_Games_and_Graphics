#include <SFML/Graphics.hpp>
//#include "SFML-2.5.1/include/SFML/Graphics.hpp"

// Window Parameters
const int S_WIDTH = 1024;
const int S_HEIGHT = 768;

sf::Vector2f viewSize(S_WIDTH, S_HEIGHT);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "SFLM Project", sf::Style::Default);

// Textures & Sprites
sf::Texture skyTexture;
sf::Sprite skySprite;


void init() {

	// Load sky Texture
	skyTexture.loadFromFile("Assets/graphics/sky.png");

	// Set and Attach a Texture to the Sprite
	skySprite.setTexture(skyTexture);
}

void draw() {
	window.draw(skySprite);
}

int main(void) {
	init();

	// Initialize Game Object
	while (window.isOpen()) {
		window.clear(sf::Color::Red);
		
		// Render Game Objects
		draw();

		window.display();
	}
}