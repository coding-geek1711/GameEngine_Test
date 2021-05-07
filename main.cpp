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


sf::Vector2f getVel(float x, float y)
{
    return sf::Vector2f({x, y});
}

int main(int argc, char **argv)
{
    std::cout << "hi this is the first iteration of Game Engine by\
    Maheswaran and S krishna Bhat\n";
    int count = 0;
    if (argc > 1)
    {
        // std::cout << "tihs is nice\n";
        if (strcmp(argv[1], "sfml") == 0)
        {
            sf::ContextSettings settings;
            settings.antialiasingLevel = 8;

            sf::RenderWindow window(sf::VideoMode(800, 800), "collision_detection.maybe", sf::Style::Default, settings);
            sf::Clock clk;
            sf::RectangleShape rectshape({50.f, 50.f});
            rectshape.setPosition({400.f, 150.f});
            rectshape.setFillColor(sf::Color::Green);
            rectshape.setOrigin(25.f, 25.f);
            sf::FloatRect flrect;

            // std::cout << "" << '\n';

            sf::CircleShape circshape(50.f);
            circshape.setFillColor(sf::Color::Magenta);
            circshape.setOrigin({25.f, 25.f});
            circshape.setPosition({550.f, 550.f});
            sf::FloatRect flcirc;

            sf::Text te;
            sf::Font f;
            f.loadFromFile("fonts/FiraCode-Regular.ttf");
            te.setFont(f);
            te.setCharacterSize(24);
            te.setFillColor(sf::Color::White);

            sf::Vector2f vel(10.f, 0.f);
            float spd = 10.f;
            // auto cvel = sf::Vector2f({0.f, -200.f});
            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
                }

                window.clear();
                flrect = rectshape.getGlobalBounds();
                // std::cout << flrect.left << '\n';
                flcirc = circshape.getGlobalBounds();

                if (!flrect.intersects(flcirc))
                {
                    flcirc.intersects(flrect) ? te.setString("True") : te.setString("False");
                    
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                    {
                        std::cout << "Up \n";
                        sf::Vector2f cvel = getVel(0.f, -100.f);
                        circshape.move(cvel * clk.getElapsedTime().asSeconds());
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                    {
                        std::cout << "Down \n";
                        sf::Vector2f cvel = getVel(0.f, 100.f);
                        circshape.move(cvel * clk.getElapsedTime().asSeconds());
                    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    {
                        std::cout << "Left \n";
                        sf::Vector2f cvel = getVel(-100.f, 0.f);
                        circshape.move(cvel * clk.getElapsedTime().asSeconds());
                    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    {
                        std::cout << "Right \n";
                        sf::Vector2f cvel = getVel(100.f, 0.f);
                        circshape.move(cvel * clk.getElapsedTime().asSeconds());
                    }



                    rectshape.rotate(spd * clk.getElapsedTime().asSeconds());
                    // rectshape.move(vel * clk.getElapsedTime().asSeconds());
                    // circshape.move(cvel * clk.getElapsedTime().asSeconds());
                    // std::cout << flrect.intersects(flcirc);

                    window.draw(rectshape);
                    window.draw(circshape);
                }

                clk.restart();


                window.draw(te);
                window.display();

            }
        }
    }

    // decide the number of enemies and stuff

    return 0;
}

// Now what?
