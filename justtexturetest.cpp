#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>

void getM_Vertices(sf::VertexArray* m_vertices, int* frame_width, int* frame_height)
{
    for(int i = 0; i < *frame_width; i++)
    {
        for(int j = 0; j < *frame_height; j++)
        {
            sf::Vertex* quad = &(*m_vertices)[(i + j * (*frame_width)) * 4];

            quad[0].position = sf::Vector2f(i * 100, j * 100);
            quad[1].position = sf::Vector2f((i + 1) * 100, j * 100);
            quad[2].position = sf::Vector2f((i + 1) * 100, (j + 1) * 100);
            quad[3].position = sf::Vector2f(i * 100, (j + 1) * 100);


            quad[0].texCoords = sf::Vector2f(0.f, 0.f);
            quad[1].texCoords = sf::Vector2f(25.f, 0.f);
            quad[2].texCoords = sf::Vector2f(25.f, 25.f);
            quad[3].texCoords = sf::Vector2f(0.f, 25.f);
        }
    }
}



int main()
{   
    int frame_height = 640;
    int frame_width = 640;
    sf::RenderWindow window(sf::VideoMode(frame_height, frame_width), "TileMap");
    
    // // multiple quads
    sf::VertexArray m_vertices;
    sf::Texture texture;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(frame_height * frame_width * 4);

    const int tiles[] = {1, 1, 1, 1, 1, 1, };
    getM_Vertices(&m_vertices, &frame_width, &frame_height);
    // for(int i = 0; i < frame_width; i ++)
    // {
    //     for(int j = 0; j < frame_height; j++)
    //     {
    //         sf::Vertex* quad = &m_vertices[(i + j * frame_width) * 4];

    //         // int tileNumber = tiles[i];
    //         quad[0].position = sf::Vector2f(i * 100, j * 100);
    //         quad[1].position = sf::Vector2f((i + 1) * 100, j * 100);
    //         quad[2].position = sf::Vector2f((i + 1) * 100, (j + 1) * 100);
    //         quad[3].position = sf::Vector2f(i * 100, (j + 1) * 100);


    //         quad[0].texCoords = sf::Vector2f(0.f, 0.f);
    //         quad[1].texCoords = sf::Vector2f(25.f, 0.f);
    //         quad[2].texCoords = sf::Vector2f(25.f, 25.f);
    //         quad[3].texCoords = sf::Vector2f(0.f, 25.f);
    //     }
    // }
        

    if(!texture.loadFromFile("tiles.png"))
    {
        std::cout << "Error loading textures" << std::endl;
    }

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }


        window.clear();
        window.draw(m_vertices, &texture);
        window.display();
    }
}