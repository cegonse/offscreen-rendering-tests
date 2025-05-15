#include <cest>
#include <raylib.h>
#include "game.h"

describe("JumpingGame", []() {
  it("builds up to 5 points after traversing 5 columns", []() {
    auto headless_mode = true;
    Game game(headless_mode);

    for (int i=0; i < 60; ++i) {
      game.DoFrame();

      if (i % 5 == 0) {
        auto filename = "build/test_" + std::to_string(i) + ".png";
        TakeScreenshot(filename.c_str());
      }
    }
  });
});
