#include <SFML/Graphics.hpp>
//#include "SFML-2.5.1/include/SFML/Graphics.hpp"

// Window Parameters
const int S_WIDTH = 1024;
const int S_HEIGHT = 768;

sf::Vector2f viewSize(S_WIDTH, S_HEIGHT);
sf::VideoMode vm(viewSize.x, viewSize.y);
sf::RenderWindow window(vm, "SFLM Project", sf::Style::Default);

// Sky Texture & Sprites
sf::Texture skyTexture;
sf::Sprite skySprite;

// Background Texture & Sprite
sf::Texture bgTexture;
sf::Sprite bgSprite;

// Hero Texture & Sprite
sf::Texture heroTexture;
sf::Sprite heroSprite;

// Player position & starting state
sf::Vector2f playerPosition;
bool playerMoving = false;

void init() {

	// Load & Attach Sky Texture
	skyTexture.loadFromFile("Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

	// Load & Attach Background Texture
	bgTexture.loadFromFile("Assets/graphics/bg.png");
	bgSprite.setTexture(bgTexture);

	// Load & Attach Hero Texture
	heroTexture.loadFromFile("Assets/graphics/hero.png");
	heroSprite.setTexture(heroTexture);
	heroSprite.setPosition(sf::Vector2f(viewSize.x / 2, viewSize.y / 2));
	heroSprite.setOrigin(heroTexture.getSize().x / 2, heroTexture.getSize().y / 2);
}

void draw() {
	window.draw(skySprite);
	window.draw(bgSprite);
	window.draw(heroSprite);
}

void updateInput() {
	
	sf::Event event;

	while (window.pollEvent(event))	{

		if (event.type == sf::Event::KeyPressed) {
			
			if (event.key.code == sf::Keyboard::Right) {
				playerMoving = true;
			}
		}

		if (event.type == sf::Event::KeyReleased) {
			if (event.key.code == sf::Keyboard::Right) {
				playerMoving = false;
			}
		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
	}
}


void update(float dt) {

	if (playerMoving) {
		heroSprite.move(50.0f * dt, 0);
	}
}

int main(void) {
	
	sf::Clock clock;
	init();

	// Initialize Game Object
	while (window.isOpen()) {
		
		updateInput();

		// Update Game
		sf::Time dt = clock.restart();
		update(dt.asSeconds());

		window.clear(sf::Color::Red);
			// Render Game Objects
			draw();
			window.display();
	}
}