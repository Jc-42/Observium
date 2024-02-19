    #pragma once
    #include <SFML/Graphics.hpp>
    class Tile{
        private:
            sf::IntRect rect;
            sf::Sprite sprite;
            int width;
            int height;
            int x;
            int y;
        public:
            Tile(int x, int y, int width, int height, sf::Texture& texture);
            Tile();
            int getX();
            int getY();
            int getWidth();
            int getHeight();
            void setX(int x);
            void setY(int y);
            void setWidth(int w);
            void setHeight(int h);
            void draw(sf::RenderWindow& window);
    };