#include <iostream>
#include <memory>
#include <fstream>

#include <SFML/Graphics.hpp>

void loadConfig(const std::string&);

int main(int argc, char *argv[])
{
    // LoadConfig from file
    loadConfig("./config.txt");
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
        
        if (circle.getPosition().x > wWidth - (circleRadius * 2)) {
            circleSpeedX = -circleSpeedX;
        }
        else if (circle.getPosition().x < 0) {
            circleSpeedX = -circleSpeedX;
        }

        if (circle.getPosition().y > wHeight - (circleRadius * 2)) {
            circleSpeedY = -circleSpeedY;
        }
        else if (circle.getPosition().y < 0) {
            circleSpeedY = -circleSpeedY;
        }

        window.clear();
        if (drawCircle)
        {
            window.draw(circle);
        }
        window.display();
    }

    return 0;
}


void loadConfig(const std::string& filename) 
{
    std::ifstream fin(filename);
    std::string className, fontFile, shapeName;
    float width, height, initX, initY, iniSpeedX, iniSpeedY, fontSze, sizeW, sizeH, radius;
    float r, g, b;

    while (fin >> className) {
        if (className == "Window") {
            fin >> width >> height;
            std::cout << "Window " << width << " " << height << std::endl;
        }
        else if (className == "Font") {
            fin >> fontFile >> fontSze >> r >> g >> b;
            std::cout << "Font " << fontFile << " " << fontSze << std::endl;
        }
        else if (className == "Rectangle") {
            fin >> shapeName >> initX >> initY >> iniSpeedX >> iniSpeedY >> r >> g >> b >> sizeW >> sizeW;
            std::cout << "Rectangle " << initX << " " << initY << std::endl;
        }
        else if (className == "Circle") {
            fin >> shapeName >> initX >> initY >> iniSpeedX >> iniSpeedY >> r >> g >> b >> radius;
            std::cout << "Circle " << initX << " " << initY << " " << r << " " << g << " " << b << std::endl;
            sf::CircleShape circle(radius, 32);
            circle.setFillColor(sf::Color(r, g, b));
            circle.setPosition(initX, initY);
        }
    }
}
