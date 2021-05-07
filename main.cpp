#include <iostream>
// #include <string>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#define frame_height 800
#define frame_width 800
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

sf::Vector2f getVel(float x, float y)
{
    return sf::Vector2f({x, y});
}

void monitorPoll(sf::RenderWindow* window, sf::Vector2f* vel)
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Right)
                vel->x = 200.f;

            else if (event.key.code == sf::Keyboard::Up)
                vel->y = -200.f;

            else if (event.key.code == sf::Keyboard::Left)
                vel->x = -200.f;

            else if (event.key.code == sf::Keyboard::Down)
                vel->y = 200.f;
            break;
        case sf::Event::KeyReleased:
            if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::Left)
                vel->x = 0.f;

            else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down)
                vel->y = 0.f;

            break;
        case sf::Event::Closed:
            window->close();
            break;
        default:
            break;
        }
    }
}


template <class T>
T renderObject(const sf::Vector2f& objectShape, const sf::Vector2f& objectPosition, sf::Color color, const sf::Vector2f& objectOrigin)
{
    T object(objectShape);
    object.setPosition(objectPosition);
    object.setFillColor(color);
    object.setOrigin(objectOrigin);
    return object;
}

template <class T>
T renderObject(const float objectShape, const sf::Vector2f& objectPosition, sf::Color color, const sf::Vector2f& objectOrigin)
{
    T object(objectShape);
    object.setPosition(objectPosition);
    object.setFillColor(color);
    object.setOrigin(objectOrigin);
    return object;
}


int main(int argc, char **argv)
{
    std::cout << "hi this is the first iteration of Game Engine by\
    Maheswaran and S krishna Bhat\n";
    if (argc > 1)
    {
        if (strcmp(argv[1], "sfml") == 0)
        {
            sf::ContextSettings settings;
            settings.antialiasingLevel = 8;

            sf::RenderWindow window(sf::VideoMode(frame_width, frame_height), "collision_detection.maybe", sf::Style::Default, settings);
            sf::Clock clk;

            sf::RectangleShape rectshape = renderObject<sf::RectangleShape>({50.f, 50.f}, {400.f, 150.f}, sf::Color::Green, {25.f, 25.f});
            sf::CircleShape circshape = renderObject<sf::CircleShape>(50.f, {550.f, 550.f}, sf::Color::Magenta, {25.f, 25.f});

            sf::FloatRect flcirc;
            sf::FloatRect flrect;

            sf::Text te;
            sf::Font f;
            f.loadFromFile("fonts/FiraCode-Regular.ttf");
            te.setFont(f);
            te.setCharacterSize(24);
            te.setFillColor(sf::Color::White);

            sf::Vector2f vel(0.f, 0.f);
            float spd = 10.f;
            while (window.isOpen())
            {
                
                monitorPoll(&window, &vel);
                window.clear();
                flrect = rectshape.getGlobalBounds();
                flcirc = circshape.getGlobalBounds();

                if (!flrect.intersects(flcirc))
                {
                    flcirc.intersects(flrect) ? te.setString("True") : te.setString("False");

                    circshape.move(vel * clk.getElapsedTime().asSeconds());

                    rectshape.rotate(spd * clk.getElapsedTime().asSeconds());

                    window.draw(rectshape);
                    window.draw(circshape);
                }

                clk.restart();

                window.draw(te);
                window.display();
            }
        }
    }
    return 0;
}

