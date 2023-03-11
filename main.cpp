#include <iostream>
#include "src/UI/UI.hpp"
#include "src/Hardware/Params.hpp"

#define WINDOW_WIDTH 2000

int main(int argc, char** argv) {
  UI ui(float(WINDOW_WIDTH)/float(SCREEN_WIDTH));
    
    while (ui.getWindowIsOpen()) {
        ui.update();
        ui.render();
    }

    return 0;
}
