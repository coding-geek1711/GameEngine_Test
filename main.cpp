#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include <typeinfo>

class TileMap : public sf::Drawable , sf::Transformable
{
    public:
        bool load_tilemap(const std::string tileset, sf::Vector2u tileSize, int* tiles, int height, int width)
        {
            /*
                height ==> rows
                width ==> cols
                
                and vertexarray fills column wise, ie col_1 first then col_2 and so on...
            */

            std::cout << "Loading textures....." << std::endl;
            if(!textures.loadFromFile(tileset))
            {
                std::cout << "Couldnt Load textures, check for asset files at "<< tileset << std::endl;
                return false;
            }
            std::cout << "Textures Loaded successfully" << std::endl;

            m_vertices.setPrimitiveType(sf::Quads);
            m_vertices.resize(height * width * 4);    

            
            // std::cout << height * width * 4 <<std::endl;
            for(int i = 0; i < width; i++)
                for(int j = 0; j < height; j++)
                {
                    int tileNumber = tiles[i + j*width];
                    // std::cout << "TileNumber is " << tileNumber << std::endl;

                    int tx = tileNumber % (textures.getSize().x / tileSize.x);
                    int ty = tileNumber / (textures.getSize().x / tileSize.x);

                    // std::cout << tx << " " << ty << std::endl;
                    sf::Vertex* quad = &m_vertices[(i + j*width) * 4];
                    // std::cout << "Quad index "<< count << std::endl;
                    
                    quad[0].position = sf::Vector2f(i * tileSize.x, j * tileSize.y);
                    quad[1].position = sf::Vector2f((i + 1) * tileSize.x, j * tileSize.y);
                    quad[2].position = sf::Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
                    quad[3].position = sf::Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

                    // Uncomment to see how the tiles are rendered sequentially
                    // std::cout << quad[0].position.x << " " << quad[0].position.y << std::endl;
                    // std::cout << quad[1].position.x << " " << quad[1].position.y << std::endl;
                    // std::cout << quad[2].position.x << " " << quad[2].position.y << std::endl;
                    // std::cout << quad[3].position.x << " " << quad[3].position.y << std::endl;

                    // quad[0].color = sf::Color::Green;
                    // quad[1].color = sf::Color::Green;
                    // quad[2].color = sf::Color::Green;
                    // quad[3].color = sf::Color::Green;


                    quad[0].texCoords = sf::Vector2f(32.f * (float)((tileNumber)), 0.f);
                    quad[1].texCoords = sf::Vector2f(32.f * (float)((tileNumber)+1), 0.f);
                    quad[2].texCoords = sf::Vector2f(32.f * (float)((tileNumber)+1), 32.f);
                    quad[3].texCoords = sf::Vector2f(32.f * (float)((tileNumber)), 32.f);

                    // quad[0].texCoords = sf::Vector2f(tx * tileSize.x, ty * tileSize.y);
                    // quad[1].texCoords = sf::Vector2f((tx + 1) * tileSize.x, ty * tileSize.y);
                    // quad[2].texCoords = sf::Vector2f((tx + 1) * tileSize.x, (ty + 1) * tileSize.y);
                    // quad[3].texCoords = sf::Vector2f(tx * tileSize.x, (ty + 1) * tileSize.y);

                    // std::cout << quad[0].texCoords.x << " " << quad[0].texCoords.y << std::endl;
                    // std::cout << quad[1].texCoords.x << " " << quad[1].texCoords.y << std::endl;
                    // std::cout << quad[2].texCoords.x << " " << quad[2].texCoords.y << std::endl;
                    // std::cout << quad[3].texCoords.x << " " << quad[3].texCoords.y << std::endl;
                }

            return true;
        }
    
    private:
        sf::VertexArray m_vertices;
        sf::Texture textures;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // GET TRANSFORM FROM TRANSFORM CLASS
            states.transform *= getTransform();

            states.texture = &textures;

            target.draw(m_vertices, states);
        }
};


struct DeclareVariables
{
    sf::RectangleShape rectshape;
    sf::CircleShape circshape;
   
    sf::FloatRect flcirc;
    sf::FloatRect flrect;

    sf::Vector2f circvel = sf::Vector2f(0.f, 0.f);
    sf::Vector2f sqrvel = sf::Vector2f(0.f, 0.f);

    float spd = 10.f;

    sf::Clock clk;
    sf::Clock clksqr;
};


void monitorPoll(sf::RenderWindow *window, sf::Vector2f *vel, sf::Vector2f* sqrvel, sf::Clock* clk, int* val)
{
    // set sqrvel
    if((int)clk->getElapsedTime().asSeconds() >= *val)
    {
        sqrvel->x *= -1;
        clk->restart();
    }

    // set circvel
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

int* invertGameArray(int arr[20*20], int* height, int* width)
{
    static int arr1[20*20];
    for(int i =0; i < *width; i++)
        for(int j = 0; j < *height; j++)
            arr1[j + i * (*height)] = arr[i + j * (*width)];
    
    return arr1;
}


bool doesCollide(sf::RectangleShape* rectshape,sf::CircleShape* circshape, sf::Vector2u* tileSize, sf::Vector2u* mapSize, int* tiles)
{
    sf::Vector2f shapePosition = circshape->getPosition();

    int tile_col = (int)(shapePosition.x / tileSize->x);
    int tile_row = (int)(shapePosition.y / tileSize->y);

    int tileNumber = tile_col * (int) mapSize->y + tile_row;

    int tileType = tiles[tileNumber];

    switch(tileType)
    {
        case 0:
            break;
        case 1:
            return true;
            break;
        case 2:
            break;
        case 3:
            break;
        default:
            return true;
            break;
    }

    tileType == 0 ? std::cout << "Grass\n" : tileType == 1 ? std::cout << "Water\n" : tileType == 2 ? std::cout << "Tree\n" : tileType == 3 ? std::cout << "Stone\n" : std::cout << "Void\n"; 

    if(rectshape->getGlobalBounds().intersects(circshape->getGlobalBounds()))
        return true;

    return false;
}

int main()
{
    int frame_width = 800, frame_height = 800;
    int height = 20, width = 20;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(frame_width, frame_height), "collision_detection.maybe", sf::Style::Default, settings);
    TileMap map;

    int tiles[] = {
        1, 1 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        1, 0 ,0, 0, 0, 1, 3, 3, 3, 3, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        1, 1 ,1, 1, 1, 1, 0, 3, 3, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 1 ,0, 0, 0, 1, 0, 3, 3, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 3, 3, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 2, 2, 0, 0, 3, 3, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 3, 3, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,2, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 
        0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 5, 
    };
    int* invertedTiles = invertGameArray(tiles, &height, &width);

    sf::Vector2u tileSize = sf::Vector2u(64,64);
    sf::Vector2u mapSize = sf::Vector2u(width, height);

    if(!map.load_tilemap("assets/textures/tiles.png", tileSize, tiles, height, width))
        return -1;

    // View Port
    sf::View view(sf::FloatRect(0.f, 0.f, (float)frame_width/2, (float)frame_height/2));
    view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
    view.setCenter(sf::Vector2f((float)frame_height/2, (float)frame_width /2));

     // Initialize variables
    DeclareVariables s = DeclareVariables();
    s.rectshape = renderObject<sf::RectangleShape>({50.f, 50.f}, {400.f, 150.f}, sf::Color::Yellow, {25.f, 25.f});
    s.circshape = renderObject<sf::CircleShape>(24.f, {320.f, 320.f}, sf::Color::Magenta, {25.f, 25.f});

    s.sqrvel.x = 100.f;
    int val = tileSize.x * 4 / (int)s.sqrvel.x;
    
    while(window.isOpen())
    {
        window.clear();
        window.setView(view);
        window.draw(map);
        monitorPoll(&window, &s.circvel, &s.sqrvel, &s.clksqr, &val);

        s.flcirc = s.circshape.getGlobalBounds();
        s.flrect = s.rectshape.getGlobalBounds();
        
        if(!doesCollide(&s.rectshape, &s.circshape, &tileSize, &mapSize, invertedTiles))
        {
            view.move(s.circvel * s.clk.getElapsedTime().asSeconds());
            
            s.circshape.move(s.circvel * s.clk.getElapsedTime().asSeconds());
            s.rectshape.rotate(s.spd * s.clk.getElapsedTime().asSeconds());
            s.rectshape.move(s.sqrvel * s.clk.getElapsedTime().asSeconds());

            window.draw(s.rectshape);
            window.draw(s.circshape);
        }
        s.clk.restart();
        
        window.display();
    }
    return 0;
}