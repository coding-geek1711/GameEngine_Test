#include <iostream>
// #include <string>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>
#include <fstream>

sf::Vector2f getVel(float x, float y)
{
    return sf::Vector2f({x, y});
}

void getM_Vertices(sf::VertexArray *m_vertices, sf::Texture* texture, sf::Vector2f tileSize,int *frame_width, int *frame_height, int tiles[100])
{
    for (int i = 0; i < *frame_width; i++)
    {
        for (int j = 0; j < *frame_height; j++)
        {

            int tileNumber = tiles[i + j * (*frame_width)];

            // std::cout << "Val is " << tileNumber << std::endl;
            sf::Vertex *quad = &(*m_vertices)[(i + j * (*frame_width)) * 4];

            quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);


            quad[0].texCoords = sf::Vector2f(32.f * (float)(tileNumber - 1), 0.f);
            quad[1].texCoords = sf::Vector2f(32.f * (float)(tileNumber), 0.f);
            quad[2].texCoords = sf::Vector2f(32.f * (float)(tileNumber), 32.f);
            quad[3].texCoords = sf::Vector2f(32.f * (float)(tileNumber - 1), 32.f);
        }
    }
}

void monitorPoll(sf::RenderWindow *window, sf::Vector2f *vel)
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
T renderObject(const sf::Vector2f &objectShape, const sf::Vector2f &objectPosition, sf::Color color, const sf::Vector2f &objectOrigin)
{
    T object(objectShape);
    object.setPosition(objectPosition);
    object.setFillColor(color);
    object.setOrigin(objectOrigin);
    return object;
}

template <class T>
T renderObject(const float objectShape, const sf::Vector2f &objectPosition, sf::Color color, const sf::Vector2f &objectOrigin)
{
    T object(objectShape);
    object.setPosition(objectPosition);
    object.setFillColor(color);
    object.setOrigin(objectOrigin);
    return object;
}

int main(int argc, char **argv)
{
    std::cout << "Some Game Engine by Maheswaran and S Krishna Bhat \n";

    if (argc > 1)
    {
        if (!strcmp(argv[1], "tilemap"))
        {

            // level textures
            int tiles[100] = {
                1,2,2,1,1,2,
                1,2,2,1,1,2,
                1,2,2,1,1,2,
                1,2,2,3,3,2,
                1,2,2,1,3,2,
                1,2,2,1,3,2,
                1,2,2,1,4,2,
            };

            int frame_width = 640, frame_height = 640;

            // Initialize vertexarray and texture classes
            sf::VertexArray m_vertices;
            sf::Texture texture;

            m_vertices.setPrimitiveType(sf::Quads);
            m_vertices.resize(frame_height * frame_width * 4);

            int height = 7, width = 6;
            float tileSize_y = (float)frame_height/height;
            float tileSize_x = (float)frame_width/width;
            getM_Vertices(&m_vertices, &texture, sf::Vector2f(tileSize_x, tileSize_y), &width, &height, tiles);

            if (!texture.loadFromFile("assets/textures/tiles.png"))
                std::cout << "Error in loading textures" << std::endl;

            // Other inits
            sf::ContextSettings settings;
            settings.antialiasingLevel = 8;

            sf::RenderWindow window(sf::VideoMode(frame_width, frame_height), "collision_detection.maybe", sf::Style::Default, settings);
            sf::Clock clk;

            sf::RectangleShape rectshape = renderObject<sf::RectangleShape>({50.f, 50.f}, {400.f, 150.f}, sf::Color::Yellow, {25.f, 25.f});
            sf::CircleShape circshape = renderObject<sf::CircleShape>(32.f, {550.f, 550.f}, sf::Color::Magenta, {25.f, 25.f});

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

            // Game Loop

            while (window.isOpen())
            {

                monitorPoll(&window, &vel);
                window.clear();
                flrect = rectshape.getGlobalBounds();
                flcirc = circshape.getGlobalBounds();
                window.draw(m_vertices, &texture);
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

        if (!strcmp(argv[1], "particles"))
        {
            std::cout << "this is where particle systems would be born\n";
        }
    }

    return 0;
}