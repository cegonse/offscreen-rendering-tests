#include <cest>
#include <raylib.h>
#include "game.h"
#include "platform-test.h"

describe("JumpingGame", []() {
  it("builds up to 5 points after traversing 5 columns", []() {
    auto headless_mode = true;
    Game game(headless_mode);

    for (int i=0; i < 160; ++i) {
      game.DoFrame();

      if (i % 9 == 0) Platform::ForceJumpKey();

      if (i % 10 == 0) {
        auto filename = "build/test_" + std::to_string(i) + ".png";
        TakeScreenshot(filename.c_str());
      }
    }
  });
});
