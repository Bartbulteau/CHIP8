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
            
            // Keyboard handling
            case sf::Event::KeyPressed: {
                switch(this->ev.key.code) {
                    case sf::Keyboard::Key::Num1: this->cpu.setKeyState(0x1, true); break;
                    case sf::Keyboard::Key::Num2: this->cpu.setKeyState(0x2, true); break;
                    case sf::Keyboard::Key::Num3: this->cpu.setKeyState(0x3, true); break;
                    case sf::Keyboard::Key::Num4: this->cpu.setKeyState(0xC, true); break;
 
                    case sf::Keyboard::Key::A: this->cpu.setKeyState(0x4, true); break;
                    case sf::Keyboard::Key::Z: this->cpu.setKeyState(0x5, true); break;
                    case sf::Keyboard::Key::E: this->cpu.setKeyState(0x6, true); break;
                    case sf::Keyboard::Key::R: this->cpu.setKeyState(0xD, true); break;

                    case sf::Keyboard::Key::Q: this->cpu.setKeyState(0x7, true); break;
                    case sf::Keyboard::Key::S: this->cpu.setKeyState(0x8, true); break;
                    case sf::Keyboard::Key::D: this->cpu.setKeyState(0x9, true); break;
                    case sf::Keyboard::Key::F: this->cpu.setKeyState(0xE, true); break;

                    case sf::Keyboard::Key::W: this->cpu.setKeyState(0xA, true); break;
                    case sf::Keyboard::Key::X: this->cpu.setKeyState(0x0, true); break;
                    case sf::Keyboard::Key::C: this->cpu.setKeyState(0xB, true); break;
                    case sf::Keyboard::Key::V: this->cpu.setKeyState(0xF, true); break;
                    default: break;
                }
                break;
            }

            case sf::Event::KeyReleased: {
                switch(this->ev.key.code) {
                    case sf::Keyboard::Key::Num1: this->cpu.setKeyState(0x1, false); break;
                    case sf::Keyboard::Key::Num2: this->cpu.setKeyState(0x2, false); break;
                    case sf::Keyboard::Key::Num3: this->cpu.setKeyState(0x3, false); break;
                    case sf::Keyboard::Key::Num4: this->cpu.setKeyState(0xC, false); break;
 
                    case sf::Keyboard::Key::A: this->cpu.setKeyState(0x4, false); break;
                    case sf::Keyboard::Key::Z: this->cpu.setKeyState(0x5, false); break;
                    case sf::Keyboard::Key::E: this->cpu.setKeyState(0x6, false); break;
                    case sf::Keyboard::Key::R: this->cpu.setKeyState(0xD, false); break;

                    case sf::Keyboard::Key::Q: this->cpu.setKeyState(0x7, false); break;
                    case sf::Keyboard::Key::S: this->cpu.setKeyState(0x8, false); break;
                    case sf::Keyboard::Key::D: this->cpu.setKeyState(0x9, false); break;
                    case sf::Keyboard::Key::F: this->cpu.setKeyState(0xE, false); break;

                    case sf::Keyboard::Key::W: this->cpu.setKeyState(0xA, false); break;
                    case sf::Keyboard::Key::X: this->cpu.setKeyState(0x0, false); break;
                    case sf::Keyboard::Key::C: this->cpu.setKeyState(0xB, false); break;
                    case sf::Keyboard::Key::V: this->cpu.setKeyState(0xF, false); break;
                    default: break;
                }
                break;
            }
            default:
                break;
        }
    }
}

void UI::update() {
    this->pollEvents();
    this->cpu.cycle();
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
            if(this->cpu.isPixelActivated(i, j)) this->screen[i][j]->setColor(sf::Color::White);
            else this->screen[i][j]->setColor(sf::Color::Black);
        }
    }
}