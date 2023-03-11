#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pixel.hpp"
#include "../Hardware/Params.hpp"

#include "UI.hpp"

UI::UI(float h) {

    this->videoMode.width = SCREEN_WIDTH*h;
    this->videoMode.height = SCREEN_HIGHT*h;
    this->window = new sf::RenderWindow(this->videoMode, "CHIP8", sf::Style::Default);
    this->window->setFramerateLimit(FRAME_RATE);

    this->screen = new Pixel**[SCREEN_WIDTH];
    for(int i = 0; i < SCREEN_WIDTH; i++) this->screen[i] = new Pixel*[SCREEN_HIGHT];
    for(int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HIGHT; j++) {
            this->screen[i][j] = new Pixel(i, j, sf::Color::Black, h);
        }
    }

    this->screen[10][10]->setColor(sf::Color::Black);
}

UI::~UI() {
    delete this->window;
    for(int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HIGHT; j++) {
            delete this->screen[i][j];
        }
    }
    for(int i = 0; i < SCREEN_WIDTH; i++) delete this->screen[i];
}

const bool UI::getWindowIsOpen() const {
    return this->window->isOpen();
}

void UI::pollEvents() {
    while(this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
                
            // Window closing
            case sf::Event::Closed:
                this->window->close();
                break;
            default:
                break;
        }
    }
}

void UI::update() {
    this->pollEvents();
    this->loadPixels();
}

void UI::render() {
    this->window->clear(sf::Color::White);
    this->drawScreen();
    this->window->display();
}

void UI::drawScreen() {
    for(int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HIGHT; j++) {
            this->window->draw(this->screen[i][j]->shape);
        }
    }
}

void UI::loadPixels() {
    for(int i = 0; i < SCREEN_WIDTH; i++) {
        for (int j = 0; j < SCREEN_HIGHT; j++) {
            this->screen[i][j]->setColor(this->cpu.getPixelColor(i, j));
        }
    }
}