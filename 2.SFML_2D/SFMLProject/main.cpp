#include <SFML/Graphics.hpp>
#include <vector>

#include "Hero.h"
#include "Enemy.h"
#include "Rocket.h"

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
void updateEnemies(float dt);
int enemySpeed[] = {-400, -500, -600};  /* Speed will depend on Enemy's spawn position */
float spawnTime = 1.125f;

float currentTime = 0.0f;

// Rocket Objects
std::vector<Rocket*> rockets;
void updateRockets(float dt);
void shoot();


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

}

void draw() {
	window.draw(skySprite);
	window.draw(bgSprite);
	window.draw(hero.getSprite());

	for (Enemy* enemy : enemies) { window.draw(enemy->getSprite()); }
	for (Rocket* rocket : rockets) { window.draw(rocket->getSprite()); }
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
		if (event.key.code == sf::Keyboard::Down) { shoot(); }
	}
}


void update(float dt) {
	hero.update(dt);
	
	currentTime += dt;
	// Spawn Enemies
	if (currentTime >= spawnTime) {
		spawnEnemy();
		currentTime = 0.0f;
	}

	// Update Enemies
	updateEnemies(dt);

	// Update Rockets
	updateRockets(dt);
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

	Enemy* enemy = new Enemy();
	enemy->init("Assets/graphics/enemy.png", enemyPos, speed);

	enemies.push_back(enemy);

}

void updateEnemies(float dt) {
	for (int i = 0; i < enemies.size(); i++) {

		Enemy* enemy = enemies[i];
		enemy->update(dt);

		if (enemy->getSprite().getPosition().x < 0) {
			enemies.erase(enemies.begin() + i);
			delete(enemy);
		}

	}
}

void shoot() {
	
	Rocket* rocket = new Rocket();

	rocket->init("Assets/graphics/rocket.png", hero.getSprite().getPosition(), 400.0f);
	rockets.push_back(rocket);
}

void updateRockets(float dt) {
	for (int i = 0; i < rockets.size(); i++) {

		Rocket* rocket = rockets[i];
		rocket->update(dt);

		if (rocket->getSprite().getPosition().x > viewSize.x) {
			rockets.erase(rockets.begin() + i);
			delete(rocket);
		}
	}
}