#ifndef PIXEL_HPP
#define PIXEL_HPP

#include <SFML/Graphics.hpp>

class Pixel {
public:
    // Constructor / Destructor
    Pixel(int x, int y, sf::Color color, float h);
    virtual ~Pixel();
    
    // Getters
    
    // Setters
    void setPosition(int x, int y);
    void setColor(sf::Color color);

    sf::RectangleShape shape;
    
private:
    // Private variables
    float h;
    // Private functions
};

#endif