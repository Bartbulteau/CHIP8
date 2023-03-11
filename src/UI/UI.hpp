#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pixel.hpp"
#include "../Hardware/Params.hpp"

class UI {
public:
    UI(float h);
    virtual ~UI();

    const bool getWindowIsOpen() const;
    void update();
    void render();
    void pollEvents();

private:

    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    Pixel*** screen;

    void drawScreen();
};

#endif