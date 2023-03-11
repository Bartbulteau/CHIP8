#include <SFML/Graphics.hpp>

#include "Pixel.hpp"

// Constructor / Destructor
Pixel::Pixel(int x, int y, sf::Color color, float h) : h(h) {
    this->setPosition(x, y);
    this->setColor(color);
}

Pixel::~Pixel() {
    
}

// Getters

// Setters
void Pixel::setPosition(int x, int y) {
    shape.setPosition(x*h, y*h);
    shape.setSize(sf::Vector2f(h, h));
}

void Pixel::setColor(sf::Color color) {
    shape.setFillColor(color);
}