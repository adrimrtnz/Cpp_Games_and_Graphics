#include "Hero.h"

// Constructor and Destructor
Hero::Hero() {}
Hero::~Hero() {}

void Hero::init(std::string textureName, sf::Vector2f position, float mass) {

	m_position = position;
	m_mass = mass;

	m_grounded = false;

	// Load texture
	m_texture.loadFromFile(textureName.c_str());

	// Create Sprite and Attach the Texture
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_sprite.setOrigin(m_texture.getSize().x / 2, m_texture.getSize().y / 2);

}

void Hero::update(float dt) {

	m_force -= m_mass * M_GRAVITY * dt;

}