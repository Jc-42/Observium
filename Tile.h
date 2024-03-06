    #pragma once
    #include <SFML/Graphics.hpp>
    class Tile{
        private:
            sf::Sprite sprite;
            int radius;
            int x;
            int y;
            sf::CircleShape* hexagon;
        public:
            std::string tag;
            Tile(double x, double y, int radius, sf::Texture& texture, std::string tag);
            Tile();
            int getX(){
                return x;
            }
            int getY(){
                return y;
            }
            int getRadius(){
                return radius;
            }
            void setX(int x){
                this->x = x;
            }
            void setY(int y){
                this->y = y;
            }
            void setRadius(int radius){
                this->radius = radius;
                sprite.setScale(sprite.getTexture()->getSize().x / radius, sprite.getScale().y);
            }
            void draw(sf::RenderWindow& window, double offsetX, double offsetY);
    };