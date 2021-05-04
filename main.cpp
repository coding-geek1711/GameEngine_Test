#include <iostream>
// #include <string>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


/*
    Some Useful Functions:-
    1. VideoMode sets video frame size
    2. CircleShape is for drawing circle ==> radius float
    3. RectangleShape for rectangle and so on ==> {width, height} (float)
    4. Top Left is (0,0) and downwards y is +ve
    5. Time module sets time
    6. Clock module starts a clock
    7. setFillColor changes color
    8. setOrigin is used to set origin of the object relative to sprite
    9. setPosition is used to set absolute position of sprite in frame
    10. rotate rotates the object
*/

#define frame_height 200
#define frame_width 400

#define rect_dims {100.f, 50.f}

int main(int argc, char **argv)
{
    std::cout << "hi this is the first iteration of Game Engine by\
    Maheswaran and S krishna Bhat\n";

    if (argc > 1)
    {
        // std::cout << "tihs is nice\n";
        if (strcmp(argv[1], "sfml") == 0)
        {
            sf::RenderWindow window(sf::VideoMode(frame_width, frame_height), "SFML works!");
            sf::RectangleShape shape(rect_dims);
            
            sf::Clock clock;
            sf::Time prevTime = sf::seconds(0.f);
            shape.setOrigin({50.f, 25.f});
            shape.setFillColor(sf::Color::Green);
            shape.setPosition({frame_width/2.f - 50.f, frame_height/2.f - 25.f});
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                sf::Time elapsedTime = clock.getElapsedTime();

                if(elapsedTime.asMicroseconds() - prevTime.asMicroseconds() > 1)
                {
                    // std::cout << "Time logged" << std::endl;
                    shape.rotate(0.1f);
                    prevTime = elapsedTime;

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
