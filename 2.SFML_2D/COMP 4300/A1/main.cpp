#include <iostream>
#include <memory>
#include <fstream>

#include <SFML/Graphics.hpp>

int main(int argc, char *argv[])
{
    // create a new window of size w*h pixels
    // top-left of the window is (0,0) and bottom-right is (w,h)
    // read this from the config file
    const int wWidth = 1280;
    const int wHeight = 720;

    sf::RenderWindow window(sf::VideoMode(wWidth, wHeight), "Assigment 1");
    window.setFramerateLimit(60);

    // initialize IMGUI and create a clock used for its internal timing
    // TODO
    sf::Clock deltaClock;

    float c[3] = { 0.0f, 1.0f, 1.0f };

    float circleRadius = 50;
    int circleSegments = 32;
    float circleSpeedX = 1.0f;
    float circleSpeedY = 0.5f;
    bool drawCircle = true;
    bool drawText = true;

    // create the SFML circle shape based on our parameters
    sf::CircleShape circle(circleRadius, circleSegments);
    circle.setPosition(10.0f, 10.0f);

    // main loop - continues for each frame while window is open
    while (window.isOpen())
    {
        // event handling
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed)
            {
                // print the key that was pressed to the console
                std::cout << "Key pressed with code = " << event.key.code << std::endl;
            }
        }

        // set the circle properties, because they may have been updated with the ui
        circle.setFillColor(sf::Color(c[0] * 255, c[1] * 255, c[2] * 255));
        circle.setPointCount(circleSegments);
        circle.setRadius(circleRadius);

        // basic animation
        circle.setPosition(circle.getPosition().x + circleSpeedX, circle.getPosition().y + circleSpeedY);

        window.clear();
        if (drawCircle)
        {
            window.draw(circle);
        }
        window.display();
    }

    return 0;
}
