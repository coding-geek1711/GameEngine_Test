#include <iostream>
// #include <string>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

int main(int argc, char **argv)
{
    std::cout << "hi this is the first iteration of Game Engine by \
Maheswaran and S krishna Bhat\n";

    if (argc > 1)
    {
        // std::cout << "tihs is nice\n";
        if (strcmp(argv[1], "sfml") == 0)
        {
            sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
            sf::Clock clk;
            sf::RectangleShape rectshape({50.f, 50.f});
            rectshape.setPosition({100.f, 100.f});
            rectshape.setFillColor(sf::Color::Green);
            rectshape.setOrigin(25.f, 25.f);

            sf::CircleShape circshape(50.f);
            circshape.setFillColor(sf::Color::Magenta);
            circshape.setOrigin({25.f, 25.f});
            circshape.setPosition({150.f, 150.f});

            sf::Vector2f vel(10.f, 0.f);
            float spd = 10.f;
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }
                rectshape.rotate(spd * clk.getElapsedTime().asSeconds());
                rectshape.move(vel * clk.getElapsedTime().asSeconds());
                circshape.move(sf::Vector2f({0.f, -10.f}) * clk.getElapsedTime().asSeconds());
                clk.restart();
                window.clear();
                window.draw(rectshape);
                window.draw(circshape);
                window.display();
            }
        }
        // std::cout << argv[1];
    }

    return 0;
}

// Now what?
