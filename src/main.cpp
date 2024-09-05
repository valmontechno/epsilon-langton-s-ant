#include "eadkpp.h"

using namespace EADK;

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "Langton's ant";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main() {
  bool grid[Screen::Height][Screen::Width];

  int x = Screen::Width / 2;
  int y = Screen::Height / 2;
  int direction = 0;

  bool isFast = false;

  for (int i = 0; i < Screen::Height; i++) {
    for (int j = 0; j < Screen::Width; j++) {
      grid[i][j] = false;
    }
  }

  Display::pushRectUniform(Screen::Rect, 0xeeeeee);

  Keyboard::State keyState;

  while (true) {
    keyState = Keyboard::scan();
    
    direction = (direction + (grid[y][x] ? 1 : -1) + 4) % 4;

    grid[y][x] = ! grid[y][x];

    Display::pushRectUniform(Rect(x, y, 1, 1), grid[y][x] ? 0x414041 : 0xeeeeee);

    switch (direction) {
      case 0: y--; break;
      case 1: x++; break;
      case 2: y++; break;
      case 3: x--; break;
    }

    x = (x + Screen::Width) % Screen::Width;
    y = (y + Screen::Height) % Screen::Height;

    if (!isFast) {
      Timing::msleep(1);
    }

    if (keyState.keyDown(Keyboard::Key::Shift)) {
      isFast = ! isFast;
      do {
        keyState = Keyboard::scan();
      } while (keyState.keyDown(Keyboard::Key::Shift));
    }

    if (keyState.keyDown(Keyboard::Key::Home) || keyState.keyDown(Keyboard::Key::Back)) return 0;
  }
}
