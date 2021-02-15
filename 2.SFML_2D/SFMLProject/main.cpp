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

	// Draw a circle
	sf::CircleShape circle(100);
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(viewSize.x / 2, viewSize.y / 2);
	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));

	// Draw a triangle
	sf::ConvexShape triangle;
	triangle.setPointCount(3);
	triangle.setPoint(0, sf::Vector2f(-100, 0));
	triangle.setPoint(1, sf::Vector2f(0, -100));
	triangle.setPoint(2, sf::Vector2f(100, 0));
	triangle.setFillColor(sf::Color(128, 0, 128, 255));	// Color(Red, Green, Blue, Alpha);
	triangle.setPosition(viewSize.x / 2, viewSize.y / 2);

	// Initialize Game Object
	while (window.isOpen()) {
		
		// Handle Keyboard Events
		// Update Game Objects in the scene

		window.clear(sf::Color::Red);
		// Render Game Objects
		window.draw(rect);
		window.draw(circle);
		window.draw(triangle);

		window.display();
	}
}