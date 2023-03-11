#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pixel.hpp"
#include "../Hardware/Params.hpp"
#include "../Hardware/CPU.hpp"

class UI {
public:
    UI(float h);
    virtual ~UI();

    const bool getWindowIsOpen() const;
    void update();
    void render();
    void pollEvents();

private:

    // Emulator
    CPU cpu;

    //Window and events
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    Pixel*** screen;

    // rendering
    void drawScreen();
    void loadPixels();
};

#endif