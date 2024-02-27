    #pragma once
    #include <SFML/Graphics.hpp>
    class Tile{
        private:
            sf::Sprite sprite;
            int width;
            int x;
            int y;
            sf::CircleShape* hexagon;
        public:
            std::string tag;
            Tile(double x, double y, int width, sf::Texture& texture, std::string tag);
            Tile();
            int getX();
            int getY();
            int getWidth();
            void setX(int x);
            void setY(int y);
            void setWidth(int w);
            void draw(sf::RenderWindow& window, double offsetX, double offsetY);
    };