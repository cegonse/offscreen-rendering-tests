#include <cest>
#include "game.h"

describe("JumpingGame", []() {
  it("builds up to 5 points after traversing 5 columns", []() {
    auto headless_mode = true;
    Game game(headless_mode);

    game.DoFrame();
  });
});
