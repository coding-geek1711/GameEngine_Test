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


bool collision_detection(sf::RectangleShape* rectshape,sf::CircleShape* circshape, sf::Vector2f* tileSize, sf::Vector2f* frameSize, sf::Vector2f* map, int* tiles)
{
    bool val = false;
    sf::FloatRect fltrect = rectshape->getGlobalBounds();
    sf::FloatRect fltcirc = circshape->getGlobalBounds();
    sf::Vector2f shapePosition = circshape->getPosition();

    int tile_col = (int)(shapePosition.x / tileSize->x);
    int tile_row = (int)(shapePosition.y / tileSize->y);

    int tileNumber = tile_col * (int) map->y + tile_row;

    int tileType = *(tiles + tileNumber);


    switch(tileType)
    {
        case 1:
            std::cout << "Grass \n";
            break;
        
        case 2:
            std::cout << "Water \n";
            // return true;
            break;
        
        case 3:
            std::cout << "Tree \n";
            break;

        case 4:
            std::cout << "Stone \n";
            break;
    }

    if(fltcirc.intersects(fltrect))
        return true;

    return false;
}


int* gameArray(int arr[100])
{
    static int arr1[100];
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            arr1[j + i * 7] = arr[i + j * 6];
        }
    }
    return arr1;    
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
                4,2,2,1,1,2,
                1,2,3,1,1,2,
                1,2,3,1,1,2,
                1,2,2,3,3,2,
                1,1,2,1,3,2,
                1,1,2,1,3,2,
                1,2,2,1,4,2,
            };
            int* tilesInverted;
            tilesInverted = gameArray(tiles);
            // std::cout << *tilesInverted << std::endl;
            int frame_width = 640, frame_height = 640;

            // Initialize vertexarray and texture classes
            sf::VertexArray m_vertices;
            sf::Texture texture;

            m_vertices.setPrimitiveType(sf::Quads);
            m_vertices.resize(frame_height * frame_width * 4);

            int height = 7, width = 6;
            sf::Vector2f map = sf::Vector2f(width, height);
            sf::Vector2f frameSize = sf::Vector2f(frame_width, frame_height);
            sf::Vector2f tileSize = sf::Vector2f((float)frame_width/width, (float)frame_height/height);
            // float tileSize_y = (float)frame_height/height;
            // float tileSize_x = (float)frame_width/width;
            getM_Vertices(&m_vertices, &texture, tileSize, &width, &height, tiles);

            if (!texture.loadFromFile("assets/textures/tiles.png"))
                std::cout << "Error in loading textures" << std::endl;

            // Other inits
            sf::ContextSettings settings;
            settings.antialiasingLevel = 8;

            sf::RenderWindow window(sf::VideoMode(frame_width, frame_height), "collision_detection.maybe", sf::Style::Default, settings);
            sf::Clock clk;
            
            sf::View view(sf::FloatRect(0.f, 0.f, (float)320, (float)320));
            view.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));
            view.setCenter(sf::Vector2f(320.f, 320.f));
            sf::RectangleShape rectshape = renderObject<sf::RectangleShape>({50.f, 50.f}, {400.f, 150.f}, sf::Color::Yellow, {25.f, 25.f});
            sf::CircleShape circshape = renderObject<sf::CircleShape>(32.f, {320.f, 320.f}, sf::Color::Magenta, {25.f, 25.f});

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
                window.setView(view);
                flrect = rectshape.getGlobalBounds();
                flcirc = circshape.getGlobalBounds();
                bool doesCollide = collision_detection(&rectshape, &circshape, &tileSize, &frameSize, &map, tilesInverted);
                window.draw(m_vertices, &texture);
                if (!doesCollide)
                {
                    flcirc.intersects(flrect) ? te.setString("True") : te.setString("False");
                    view.move(vel * clk.getElapsedTime().asSeconds());
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