#include <SFML/Graphics.hpp>
#include <vector>

#include "Hero.h"
#include "Enemy.h"

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

// Hero Object
Hero hero;
const float JUMP_FORCE = 750.0f;

// Enemy Objects
std::vector<Enemy*> enemies;
void spawnEnemy();
int enemySpeed[] = {-400, -500, -600};


void init() {

	// Randomness is needed to the Enemy's spawn position
	srand((int)time(0));

	// Load & Attach Sky Texture
	skyTexture.loadFromFile("Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

	// Load & Attach Background Texture
	bgTexture.loadFromFile("Assets/graphics/bg.png");
	bgSprite.setTexture(bgTexture);

	// Load & Attach Hero Texture
	hero.init("Assets/graphics/hero.png", sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);

	// Load & Attach Enemy Texture


}

void draw() {
	window.draw(skySprite);
	window.draw(bgSprite);
	window.draw(hero.getSprite());
}

void updateInput() {
	
	sf::Event event;

	while (window.pollEvent(event))	{

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up) {
				hero.jump(JUMP_FORCE);
			}
		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
	}
}


void update(float dt) {
	hero.update(dt);
}

int main(void) {
	
	sf::Clock clock;
	init();

	// Main game loop
	while (window.isOpen()) {
		
		updateInput();

		// Update Game
		sf::Time dt = clock.restart();
		update(dt.asSeconds());

		window.clear(sf::Color::Red);
		draw();
		window.display();
	}
}

void spawnEnemy() {

	// Generate a random number between 0 and 2
	int randLoc = rand() % 3;

	sf::Vector2f enemyPos;
	float speed = enemySpeed[randLoc];

	switch (randLoc) {
	case 0:
		enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.75f);
		break;
		
	case 1:
		enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.60f);
		break;

	case 2:
		enemyPos = sf::Vector2f(viewSize.x, viewSize.y * 0.40f);
		break;

	default:
		printf("Incorrect 'y' value\n");
		return;
	}

}