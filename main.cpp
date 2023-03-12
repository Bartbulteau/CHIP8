#include <iostream>
#include "src/UI/UI.hpp"
#include "src/Hardware/Params.hpp"

#define WINDOW_WIDTH 1500

int main(int argc, char** argv) {

  char * filename;
  if(argc >= 2) {
    filename = argv[1];
  } else {
    std::cout << "Error no ROM to load. Try CHIP8 path/to/rom" << std::endl;
    return 0;
  }

  UI ui(float(WINDOW_WIDTH)/float(SCREEN_WIDTH));
  ui.cpu.loadGame(filename);

  while (ui.getWindowIsOpen()) {
    ui.update();
    ui.render();
  }

  return 0;
}
