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
            sf::CircleShape shape(100.f);
            shape.setFillColor(sf::Color::Green);

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear();
                window.draw(shape);
                window.display();
            }
        }
        // std::cout << argv[1];
    }

    return 0;
}

// Now what?
