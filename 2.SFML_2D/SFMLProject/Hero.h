#pragma once
#include <SFML/Graphics.hpp>

const int S_HEIGHT = 768;

class Hero {

	public:
		Hero();
		~Hero();

		void init(std::string textureName, sf::Vector2f position, float mass);
		void update(float dt);
		void jump(float velocity);
		sf::Sprite getSprite();

	private:
		sf::Texture m_texture;
		sf::Sprite m_sprite;
		sf::Vector2f m_position;

		const float M_GRAVITY = 9.81f;
		int jumpCount = 0;
		float m_mass;
		float m_velocity;
		bool m_grounded;

};