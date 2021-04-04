#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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

int score = 0;
bool gameover = true;
void updateScore(int score);

// Text Object
sf::Font headingFont;
sf::Text headingText;
sf::Text scoreText;
sf::Text tutorialText;

// Music & SFX Object
sf::Music bgMusic;
sf::SoundBuffer fireBuffer, hitBuffer, jumpBuffer;
sf::Sound fireSound(fireBuffer), hitSound(hitBuffer), jumpSound(jumpBuffer);

// Rocket Objects
std::vector<Rocket*> rockets;
void updateRockets(float dt);
void shoot();

bool isColliding(sf::Sprite sprite1, sf::Sprite sprite2);
void reset();


void init() {

	// Randomness is needed to the Enemy's spawn position
	srand((int)time(0));

	//Audio
	bgMusic.openFromFile("Assets/audio/bgMusic.wav");
	bgMusic.play();
	//bgMusic.setVolume(50);	/* Uncomment if you want to change the background music volume. The value is between 0 and 100. */

	hitBuffer.loadFromFile("Assets/audio/hit.wav");
	fireBuffer.loadFromFile("Assets/audio/fire.wav");
	jumpBuffer.loadFromFile("Assets/audio/jump.wav");

	// Load & Attach Sky Texture
	skyTexture.loadFromFile("Assets/graphics/sky.png");
	skySprite.setTexture(skyTexture);

	// Load & Attach Background Texture
	bgTexture.loadFromFile("Assets/graphics/bg.png");
	bgSprite.setTexture(bgTexture);

	// Load & Set Heading Text
	headingFont.loadFromFile("Assets/fonts/TimKid.ttf");
	headingText.setFont(headingFont);
	headingText.setString("Tiny Bazooka");
	headingText.setCharacterSize(85);
	headingText.setFillColor(sf::Color::Red);

	sf::FloatRect headingBounds = headingText.getLocalBounds();
	headingText.setOrigin(headingBounds.width / 2, headingBounds.height / 2);
	headingText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));

	// Score Text
	scoreText.setFont(headingFont);
	scoreText.setCharacterSize(45);
	scoreText.setFillColor(sf::Color::Red);
	updateScore(score);

	// Tutorial Text
	tutorialText.setFont(headingFont);
	tutorialText.setString("Press Down Arrow to Fire and Start Game, Up Arrow to Jump");
	tutorialText.setCharacterSize(35);
	tutorialText.setFillColor(sf::Color::Red);

	sf::FloatRect tutorialBounds = tutorialText.getLocalBounds();
	tutorialText.setOrigin(tutorialBounds.width / 2, tutorialBounds.height / 2);
	tutorialText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.2f));

	// Load & Attach Hero Texture
	hero.init("Assets/graphics/heroAnim.png", 4, 1.0f, sf::Vector2f(viewSize.x * 0.25f, viewSize.y * 0.5f), 200);

}

void draw() {
	window.draw(skySprite);
	window.draw(bgSprite);
	window.draw(hero.getSprite());

	if (gameover) {
		window.draw(headingText);
		window.draw(tutorialText);
	}
	else {
		window.draw(scoreText);
	}

	for (Enemy* enemy : enemies) { window.draw(enemy->getSprite()); }
	for (Rocket* rocket : rockets) { window.draw(rocket->getSprite()); }
}

void updateInput() {
	
	sf::Event event;

	while (window.pollEvent(event))	{

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Up) {
				hero.jump(JUMP_FORCE);
				jumpSound.play();
			}
		}

		if (event.key.code == sf::Keyboard::Escape || event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.key.code == sf::Keyboard::Down) { 
			if (!gameover) {
				shoot();
			}
			else {
				gameover = false;
				reset();
			}
		}
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

	// Check collisions
	for (int i = 0; i < rockets.size(); i++) {
		for (int j = 0; j < enemies.size(); j++) {
			Rocket* rocket = rockets[i];
			Enemy* enemy = enemies[j];

			if (isColliding(rocket->getSprite(), enemy->getSprite())) {
				
				hitSound.play();
				updateScore(++score);
				
				rockets.erase(rockets.begin() + i);
				enemies.erase(enemies.begin() + j);

				delete(rocket);
				delete(enemy);

				printf("rocket intersects enemy \n");
			}

		}
	}
}

int main(void) {
	
	sf::Clock clock;
	init();

	// Main game loop
	while (window.isOpen()) {
		
		updateInput();

		// Update Game
		sf::Time dt = clock.restart();
		if (!gameover) {
			update(dt.asSeconds());
		}
			
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
			gameover = true;
		}

	}
}

void shoot() {
	
	Rocket* rocket = new Rocket();

	rocket->init("Assets/graphics/rocket.png", sf::Vector2f(hero.getSprite().getPosition().x -130, hero.getSprite().getPosition().y), 400.0f);
	rockets.push_back(rocket);
	fireSound.play();
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

void updateScore(int score) {
	
	std::string finalScore = "Score: " + std::to_string(score);
	scoreText.setString(finalScore);
	sf::FloatRect scoreBounds = scoreText.getLocalBounds();
	scoreText.setOrigin(scoreBounds.width / 2, scoreBounds.height / 2);
	scoreText.setPosition(sf::Vector2f(viewSize.x * 0.5f, viewSize.y * 0.10f));
}

bool isColliding(sf::Sprite sprite1, sf::Sprite sprite2) {

	sf::FloatRect shape1 = sprite1.getGlobalBounds();
	sf::FloatRect shape2 = sprite2.getGlobalBounds();

	if (shape1.intersects(shape2)) { return true; }
	return false;
}

void reset() {

	score = 0;
	updateScore(score);
	currentTime = 0.0f;

	for (Enemy* enemy : enemies) { delete(enemy); }
	for (Rocket* rocket : rockets) { delete(rocket); }

	enemies.clear();
	rockets.clear();

}